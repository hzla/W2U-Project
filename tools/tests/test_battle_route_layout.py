"""Check the internal route layout without narrowing mechanic IDs or API fields."""
import importlib.util
import json
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location("registry_generator", ROOT / "tools/generate_w2u_battle_registry.py")
generator = importlib.util.module_from_spec(spec)
spec.loader.exec_module(generator)


class BattleRouteLayout(unittest.TestCase):
    def test_loader_paths_and_buffer_bounds(self):
        registry = generator.load_registry(ROOT / "src/pokeweb_gameplay/battle_modules/registry.json")
        text = (ROOT / "src/pokeweb_gameplay/w2u_battle_module_loader.cpp").read_text()
        body = re.search(r"bool BuildModulePath\(.*?^\}", text, re.S | re.M).group()
        source = '#include <cstring>\ntypedef unsigned u32;\n'
        source += f'static const char sBattleModuleRoot[]="{registry["output_root"]}/";\n' + body
        source += '\nint main() { char buffer[66];\n'
        for module in registry["modules"]:
            relative = f'{module["name"]}.dll'
            full = f'{registry["output_root"]}/{relative}'
            source += (f'if (!BuildModulePath(buffer,64,"{relative}") || '
                       f'std::strcmp(buffer,"{full}")) return 1;\n')
        source += r'''
            for (u32 size=0;size<64;++size) {
                std::memset(buffer,0x5a,sizeof(buffer));
                bool success=BuildModulePath(buffer+1,size,"moves/terrain.dll");
                if (success!=(size>std::strlen("lib/w2u_battle/moves/terrain.dll"))) return 2;
                if (buffer[0]!=0x5a || buffer[size+1]!=0x5a) return 3;
            }
            if (BuildModulePath(0,64,"moves/terrain.dll") || BuildModulePath(buffer,64,0)) return 4;
            return 0;
        }
'''
        with tempfile.TemporaryDirectory(prefix="w2u-paths-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_registry_rejects_paths_larger_than_loader_buffer(self):
        registry = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
        registry["modules"][0]["name"] = "abilities/" + "x" * 64
        with tempfile.TemporaryDirectory(prefix="w2u-paths-") as directory:
            path = Path(directory) / "registry.json"
            path.write_text(json.dumps(registry))
            with self.assertRaisesRegex(RuntimeError, "buffer"):
                generator.load_registry(path)

    def test_generated_routes_preserve_every_key_and_module(self):
        registry = generator.load_registry(ROOT / "src/pokeweb_gameplay/battle_modules/registry.json")
        modules = sorted(registry["modules"], key=lambda module: module["id"])
        entries = [(module["id"], *entry[:2]) for module in modules for entry in module["entries"]]
        names = list(dict.fromkeys(entry[2] for entry in entries))
        # Deliberately use IDs above 255, including the full u16 limit. The
        # private route kind/module are bytes; public mechanic IDs stay u16.
        values = {name: 65535 - index if name.isidentifier() else int(name) for index, name in enumerate(names)}
        source = "typedef unsigned char u8; typedef unsigned short u16; typedef unsigned u32;\n"
        source += "enum {" + ",".join(f"{name}={index}" for index, name in enumerate(generator.KIND_ENUM.values())) + "};\n"
        source += "enum {" + ",".join(f"{name}={value}" for name, value in values.items() if name.isidentifier()) + "};\n"
        source += generator.render_cpp(registry)
        source += "int main() {\n"
        for index, (module_id, kind, name) in enumerate(entries):
            source += (f"if (sBattleMechanicRoutes[{index}].id != {values[name]} || "
                       f"sBattleMechanicRoutes[{index}].kind != {generator.KIND_ENUM[kind]} || "
                       f"sBattleMechanicRoutes[{index}].module != {module_id}) return 1;\n")
        source += "return 0; }\n"
        with tempfile.TemporaryDirectory(prefix="w2u-routes-") as directory:
            executable = Path(directory) / "check"
            subprocess.run(["c++", "-std=c++11", "-x", "c++", "-o", str(executable), "-"],
                           input=source, text=True, check=True)
            subprocess.run([str(executable)], check=True)

    def test_public_api_remains_fixed_width(self):
        api = (ROOT / "include/w2u_battle_module_api.h").read_text()
        self.assertIn("u16 kind;", api)
        self.assertIn("u16 id;", api)

    def test_capacity_cannot_narrow_module_indices(self):
        registry = json.loads((ROOT / "src/pokeweb_gameplay/battle_modules/registry.json").read_text())
        registry["capacity"] = 257
        with tempfile.TemporaryDirectory(prefix="w2u-routes-") as directory:
            path = Path(directory) / "registry.json"
            path.write_text(json.dumps(registry))
            with self.assertRaisesRegex(RuntimeError, "capacity"):
                generator.load_registry(path)


if __name__ == "__main__":
    unittest.main()
