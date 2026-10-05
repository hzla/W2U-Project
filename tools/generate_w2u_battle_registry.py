#!/usr/bin/env python3
"""Validate the battle-module registry and generate the resident C++ routes."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


KIND_ENUM = {
    "ability": "W2U_MECHANIC_ABILITY",
    "move": "W2U_MECHANIC_MOVE",
    "item": "W2U_MECHANIC_ITEM",
    "field": "W2U_MECHANIC_FIELD",
    "side": "W2U_MECHANIC_SIDE",
    "position": "W2U_MECHANIC_POSITION",
}

EXPECTED_PRIMARY_COUNTS = {
    "ability": 134,    # + Intimidate (Guard Dog), + 7 terrain-dependent (mb_terrain), + 13 wave C (mb_hooked, Dragonize)
    "move": 101,
    "item": 13,
}


def enum_name(name: str) -> str:
    return "W2U_MODULE_" + re.sub(r"[^A-Z0-9]+", "_", name.upper())


def slug(name: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", name.lower()).strip("_")


def getter_name(name: str) -> str:
    return "W2U_GetStaticBattleModuleApi_" + slug(name).upper()


def source_family(module: dict) -> str:
    source = module["source"]
    if source.startswith("abilities"):
        return "ABILITIES"
    if source == "items":
        return "ITEMS"
    if source.startswith("moves"):
        return "MOVES"
    raise RuntimeError(f"{module['name']}: unsupported source family {source!r}")


def entry_key(kind: str, mechanic_id: str) -> str:
    return f"{kind}:{mechanic_id}"


def entry_config(registry: dict, module: dict, kind: str, mechanic_id: str) -> dict:
    config = dict(registry["entry_defaults"])
    config.update(module.get("entry_overrides", {}).get(entry_key(kind, mechanic_id), {}))
    return config


def load_registry(path: Path) -> dict:
    registry = json.loads(path.read_text())
    modules = registry.get("modules")
    if not isinstance(modules, list) or not modules:
        raise RuntimeError("registry has no modules")
    if registry.get("abi_version") != 1:
        raise RuntimeError("registry ABI version must be 1")
    capacity = registry.get("capacity")
    if not isinstance(capacity, int) or capacity <= 0 or capacity > 256 or len(modules) > capacity:
        raise RuntimeError("module count exceeds fixed loader capacity")
    if registry.get("output_root") != "lib/w2u_battle":
        raise RuntimeError("output_root must be lib/w2u_battle")
    defaults = registry.get("entry_defaults", {})
    if defaults.get("handler_count") != "array" or defaults.get("priority") != 0xFFFF:
        raise RuntimeError("entry defaults must use array counts and priority 0xFFFF")

    names: set[str] = set()
    ids: set[int] = set()
    keys: set[tuple[str, str]] = set()
    tables: set[str] = set()
    primary_counts = dict.fromkeys(EXPECTED_PRIMARY_COUNTS, 0)
    for module in modules:
        module_id = module.get("id")
        name = module.get("name")
        source = module.get("source")
        entries = module.get("entries")
        if not isinstance(module_id, int) or module_id < 0 or module_id >= capacity:
            raise RuntimeError(f"invalid module ID: {module_id!r}")
        if module_id in ids:
            raise RuntimeError(f"duplicate module ID {module_id}")
        ids.add(module_id)
        if not isinstance(name, str) or not name or name in names:
            raise RuntimeError(f"invalid or duplicate module name: {name!r}")
        path = Path(name)
        if path.is_absolute() or ".." in path.parts or len(path.parts) != 2:
            raise RuntimeError(f"unsafe module path: {name!r}")
        if len(f"{registry['output_root']}/{name}.dll".encode("ascii")) >= 64:
            raise RuntimeError(f"module path exceeds resident loader buffer: {name!r}")
        names.add(name)
        if not isinstance(source, str) or not source:
            raise RuntimeError(f"{name}: missing source set")
        if not isinstance(entries, list) or not entries:
            raise RuntimeError(f"{name}: no API entries")
        overrides = module.get("entry_overrides", {})
        if not isinstance(overrides, dict):
            raise RuntimeError(f"{name}: entry_overrides must be an object")
        module_keys: set[str] = set()
        for entry in entries:
            if not isinstance(entry, list) or len(entry) != 3:
                raise RuntimeError(f"{name}: malformed entry {entry!r}")
            kind, mechanic_id, table = entry
            if kind not in KIND_ENUM:
                raise RuntimeError(f"{name}: unknown mechanic kind {kind!r}")
            if not all(isinstance(value, str) and value for value in (mechanic_id, table)):
                raise RuntimeError(f"{name}: malformed mechanic/table name")
            key = (kind, mechanic_id)
            if key in keys:
                raise RuntimeError(f"duplicate mechanic registration {key}")
            keys.add(key)
            module_keys.add(entry_key(kind, mechanic_id))
            tables.add(table)
            if kind in primary_counts:
                primary_counts[kind] += 1
            config = entry_config(registry, module, kind, mechanic_id)
            handler_count = config.get("handler_count")
            priority = config.get("priority")
            if handler_count != "array" and (
                not isinstance(handler_count, int) or handler_count <= 0
            ):
                raise RuntimeError(f"{name}: invalid handler count for {key}")
            if isinstance(priority, int):
                if priority != 0xFFFF and not 0 <= priority <= 0xFF:
                    raise RuntimeError(f"{name}: invalid priority for {key}")
            elif not isinstance(priority, str) or not priority.startswith("EVENTPRI_"):
                raise RuntimeError(f"{name}: invalid priority for {key}")
        unknown_overrides = sorted(set(overrides) - module_keys)
        if unknown_overrides:
            raise RuntimeError(
                f"{name}: overrides reference unknown entries: {unknown_overrides}"
            )
        dependency = module.get("dependency")
        if dependency is not None and dependency == name:
            raise RuntimeError(f"{name}: module cannot depend on itself")

    expected_ids = set(range(len(modules)))
    if ids != expected_ids:
        raise RuntimeError(
            f"module IDs must be contiguous: expected {sorted(expected_ids)}, got {sorted(ids)}"
        )
    for module in modules:
        dependency = module.get("dependency")
        if dependency is not None and dependency not in names:
            raise RuntimeError(f"{module['name']}: unknown dependency {dependency!r}")
    if primary_counts != EXPECTED_PRIMARY_COUNTS:
        raise RuntimeError(
            f"primary mechanic counts mismatch: expected {EXPECTED_PRIMARY_COUNTS}, "
            f"got {primary_counts}"
        )
    return registry


def render_cpp(registry: dict) -> str:
    modules = sorted(registry["modules"], key=lambda module: module["id"])
    name_to_enum = {module["name"]: enum_name(module["name"]) for module in modules}
    lines = [
        "// Generated by tools/generate_w2u_battle_registry.py. Do not edit by hand.",
        "enum W2UBattleModuleId : u8 {",
    ]
    lines.extend(f"    {name_to_enum[module['name']]}," for module in modules)
    lines.extend(
        [
            "    W2U_BATTLE_MODULE_COUNT,",
            "    W2U_NO_MODULE = 0xFF,",
            "};",
            "",
            "struct W2UBattleModuleDescriptor {",
            "    const char* path; // Relative to sBattleModuleRoot; private resident layout.",
            "    u8 dependency;",
            "};",
            "",
            "struct W2UBattleMechanicRoute {",
            "    u16 id;",
            "    u8 kind;",
            "    u8 module;",
            "};",
            'static_assert(sizeof(W2UBattleMechanicRoute) == 4, "Resident mechanic routes must remain compact");',
            f'static const char sBattleModuleRoot[] = "{registry["output_root"]}/";',
            "",
            "static const W2UBattleModuleDescriptor sBattleModuleDescriptors[] = {",
        ]
    )
    for module in modules:
        dependency = module.get("dependency")
        dependency_enum = name_to_enum[dependency] if dependency else "W2U_NO_MODULE"
        path = f"{module['name']}.dll"
        lines.append(f'    {{"{path}", {dependency_enum}}},')
    lines.extend(
        [
            "};",
            "",
            "#define W2U_ROUTE(kind, id, module) {(u16)(id), (u8)(kind), (u8)(module)}",
            "",
            "static const W2UBattleMechanicRoute sBattleMechanicRoutes[] = {",
        ]
    )
    for module in modules:
        module_enum = name_to_enum[module["name"]]
        for kind, mechanic_id, _table in module["entries"]:
            lines.append(
                f"    W2U_ROUTE({KIND_ENUM[kind]}, {mechanic_id}, {module_enum}),"
            )
    lines.extend(["};", "", "#undef W2U_ROUTE", ""])
    lines.extend(
        [
            "#if defined(W2U_BATTLE_STATIC_RESOLVER_BUILD)",
            "typedef const W2UBattleModuleApi* (*W2UBattleStaticApiGetter)();",
        ]
    )
    for module in modules:
        declaration = 'extern "C" const W2UBattleModuleApi* ' + getter_name(module["name"]) + "();"
        if module.get("white2_only"):
            lines.extend(["#if !defined(W2U_TARGET_B2)", declaration, "#endif"])
        else:
            lines.append(declaration)
    if any(module.get("white2_only") for module in modules):
        lines.extend(
            [
                "#if defined(W2U_TARGET_B2)",
                "// White 2-only modules (registry \"white2_only\"): not built for Black 2.",
                "static const W2UBattleModuleApi* W2U_UnavailableStaticBattleModule() { return 0; }",
                "#endif",
            ]
        )
    lines.extend(
        [
            "",
            "static const W2UBattleStaticApiGetter sBattleStaticApiGetters[] = {",
        ]
    )
    for module in modules:
        if module.get("white2_only"):
            lines.extend(
                [
                    "#if defined(W2U_TARGET_B2)",
                    "    W2U_UnavailableStaticBattleModule,",
                    "#else",
                    f"    {getter_name(module['name'])},",
                    "#endif",
                ]
            )
        else:
            lines.append(f"    {getter_name(module['name'])},")
    lines.extend(["};", "#endif", ""])
    return "\n".join(lines)


def render_api_cpp(registry: dict) -> str:
    modules = sorted(registry["modules"], key=lambda module: module["id"])
    lines = [
        "// Generated by tools/generate_w2u_battle_registry.py. Do not edit by hand.",
        "#if defined(W2U_BATTLE_CHILD) || defined(W2U_BATTLE_STATIC_GROUPS)",
    ]
    for family in ("ABILITIES", "ITEMS", "MOVES"):
        family_modules = [
            module for module in modules if source_family(module) == family
        ]
        lines.extend(
            [
                "",
                f"#if defined(W2U_BATTLE_API_SOURCE_{family})",
            ]
        )
        if family == "ABILITIES":
            lines.extend(
                [
                    "extern BattleEventHandlerTableEntry FieldDarkAuraHandlers[];",
                    "extern BattleEventHandlerTableEntry FieldFairyAuraHandlers[];",
                ]
            )
        lines.append("#if defined(W2U_BATTLE_CHILD)")
        for index, module in enumerate(family_modules):
            directive = "#if" if index == 0 else "#elif"
            lines.append(f"{directive} W2U_BATTLE_MODULE_ID == {module['id']}")
            lines.extend(render_api_definition(registry, module, "sBattleModule", None))
        lines.extend(
            [
                "#else",
                f'#error Unsupported {family.lower()} battle module ID',
                "#endif",
                "",
                'extern "C" W2U_BATTLE_MODULE_EXPORT const W2UBattleModuleApi* '
                "W2U_GetBattleModuleApi()",
                "{",
                "    return &sBattleModuleApi;",
                "}",
                "#elif defined(W2U_BATTLE_STATIC_GROUPS)",
            ]
        )
        for module in family_modules:
            identifier = slug(module["name"])
            definition = render_api_definition(
                registry,
                module,
                f"sBattleModule_{identifier}",
                getter_name(module["name"]),
            )
            if module.get("white2_only"):
                definition = ["#if !defined(W2U_TARGET_B2)", *definition, "#endif"]
            lines.extend(definition)
        lines.extend(["#endif", f"#endif // W2U_BATTLE_API_SOURCE_{family}"])
    lines.extend(["#endif", ""])
    return "\n".join(lines)


def render_api_definition(
    registry: dict,
    module: dict,
    symbol_prefix: str,
    getter: str | None,
) -> list[str]:
    entries_symbol = symbol_prefix + "Entries"
    api_symbol = symbol_prefix + "Api"
    lines = [f"static const W2UBattleHandlerExport {entries_symbol}[] = {{"]
    for kind, mechanic_id, table in module["entries"]:
        config = entry_config(registry, module, kind, mechanic_id)
        count = config["handler_count"]
        count_expr = (
            f"(u16)W2U_ARRAY_COUNT({table})"
            if count == "array"
            else f"(u16)({count})"
        )
        priority = config["priority"]
        priority_expr = (
            "W2U_BATTLE_MODULE_DEFAULT_PRIORITY"
            if priority == 0xFFFF
            else f"(u16)({priority})"
        )
        lines.append(
            "    {"
            + f"{KIND_ENUM[kind]}, (u16)({mechanic_id}), {count_expr}, "
            + f"{priority_expr}, {table}"
            + "},"
        )
    lines.extend(
        [
            "};",
            f"static const W2UBattleModuleApi {api_symbol} = {{",
            "    W2U_BATTLE_MODULE_MAGIC,",
            "    W2U_BATTLE_MODULE_ABI_VERSION,",
            f"    (u16)W2U_ARRAY_COUNT({entries_symbol}),",
            f"    {entries_symbol},",
            "};",
        ]
    )
    if getter:
        lines.extend(
            [
                'extern "C" __attribute__((visibility("hidden"))) '
                f"const W2UBattleModuleApi* {getter}()",
                "{",
                f"    return &{api_symbol};",
                "}",
            ]
        )
    return lines


def render_meson(registry: dict) -> str:
    source_files = {
        "abilities": ["../w2u_abilities.cpp"],
        "abilities+field_effects": [
            "../w2u_abilities.cpp",
            "../w2u_field_effects.cpp",
        ],
        "abilities+strong_weather": [
            "../w2u_abilities.cpp",
            "../w2u_strong_weather.cpp",
        ],
        "items": ["../w2u_items.cpp"],
        "moves": ["../w2u_moves.cpp"],
    }
    lines = [
        "# Generated by tools/generate_w2u_battle_registry.py. Do not edit by hand.",
        "w2u_battle_module_definitions = [",
    ]
    for module in sorted(registry["modules"], key=lambda item: item["id"]):
        paths = source_files.get(module["source"])
        if module.get("extra_sources"):
            # Ported MegaB2W2 logic (src/pokeweb_gameplay/megab2w2/): the family's file plus the listed sources.
            paths = source_files[module["source"]] + [f"../{path}" for path in module["extra_sources"]]
        if not paths:
            raise RuntimeError(
                f"{module['name']}: no Meson source mapping for {module['source']!r}"
            )
        files_expr = ", ".join(f"'{path}'" for path in paths)
        lines.append("  {")
        lines.append(f"    'id': {module['id']},")
        lines.append(f"    'slug': '{slug(module['name'])}',")
        lines.append(f"    'sources': files({files_expr}),")
        lines.append("  },")
    lines.extend(["]", ""])
    return "\n".join(lines)


def check_sources(registry: dict, paths: list[Path]) -> None:
    source_text = "\n".join(path.read_text() for path in paths)
    missing_tables = sorted(
        {
            table
            for module in registry["modules"]
            for _kind, _mechanic_id, table in module["entries"]
            if table not in source_text
        }
    )
    if missing_tables:
        raise RuntimeError(
            "registry handler tables absent from grouped sources: "
            + ", ".join(missing_tables)
        )
    for family in ("ABILITIES", "ITEMS", "MOVES"):
        marker = f"W2U_BATTLE_API_SOURCE_{family}"
        if marker not in source_text:
            raise RuntimeError(f"grouped source is missing generated API marker {marker}")


def check_meson(registry: dict, path: Path) -> None:
    text = path.read_text()
    for module in registry["modules"]:
        expected = (
            "{'id': "
            + str(module["id"])
            + ", 'slug': '"
            + slug(module["name"])
            + "'"
        )
        if expected not in text and (
            f"'id': {module['id']}," not in text
            or f"'slug': '{slug(module['name'])}'," not in text
        ):
            raise RuntimeError(
                f"{module['name']}: Meson child target definition is absent or mismatched"
            )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--registry", type=Path, required=True)
    parser.add_argument("--output", type=Path)
    parser.add_argument("--check", type=Path)
    parser.add_argument("--api-output", type=Path)
    parser.add_argument("--api-check", type=Path)
    parser.add_argument("--meson-output", type=Path)
    parser.add_argument("--meson-check", type=Path)
    parser.add_argument("--meson", type=Path)
    parser.add_argument("--source", type=Path, action="append", default=[])
    parser.add_argument("--stamp", type=Path)
    args = parser.parse_args()

    if bool(args.output) == bool(args.check):
        parser.error("exactly one of --output or --check is required")

    registry = load_registry(args.registry)
    # Modules with "extra_sources" keep their handler tables in those files: check them as sources too.
    gameplay_root = args.registry.resolve().parent.parent
    for module in registry["modules"]:
        for path in module.get("extra_sources", []):
            source = gameplay_root / path
            if source not in args.source:
                args.source.append(source)
    generated = render_cpp(registry)
    generated_api = render_api_cpp(registry)
    generated_meson = render_meson(registry)
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(generated)
    elif args.check.read_text() != generated:
        raise RuntimeError(
            f"{args.check} is stale; regenerate it with --output {args.check}"
        )
    if args.api_output and args.api_check:
        parser.error("--api-output and --api-check are mutually exclusive")
    if args.api_output:
        args.api_output.parent.mkdir(parents=True, exist_ok=True)
        args.api_output.write_text(generated_api)
    elif args.api_check and args.api_check.read_text() != generated_api:
        raise RuntimeError(
            f"{args.api_check} is stale; regenerate it with --api-output {args.api_check}"
        )
    if args.meson_output and args.meson_check:
        parser.error("--meson-output and --meson-check are mutually exclusive")
    if args.meson_output:
        args.meson_output.parent.mkdir(parents=True, exist_ok=True)
        args.meson_output.write_text(generated_meson)
    elif args.meson_check and args.meson_check.read_text() != generated_meson:
        raise RuntimeError(
            f"{args.meson_check} is stale; regenerate it with --meson-output {args.meson_check}"
        )
    if args.meson:
        check_meson(registry, args.meson)
    if args.source:
        check_sources(registry, args.source)
    if args.stamp:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.touch()

    print(
        f"[+] validated {len(registry['modules'])} battle modules and "
        f"{sum(len(module['entries']) for module in registry['modules'])} API entries"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
