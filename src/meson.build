patches = []

subdir('pokedex_expansion')
subdir('type_expansion')
subdir('pwan_animation')
subdir('pokeweb_gameplay')
subdir('battle_log')

cxx = meson.get_compiler('cpp')
rpm_strip_flag = get_option('strip_rpms') ? '--strip' : 'no-strip'
# Every import of a White 2 DLL must be in the ESDB (or exported by w2u_main for a module loaded beside it).
rpm_import_verifier = meson.project_source_root() / 'tools' / 'verify_rpm_imports.py'
checked_rpm_packager = meson.project_source_root() / 'tools' / 'package_rpm_checked.py'
checked_rpm_depend_files = [
  checked_rpm_packager,
  meson.project_source_root() / 'tools' / 'audit_white2upgrade_battle_heap.py',
]
w2u_cpp_args = cpp_args + ['-DW2U_DYNAMIC_BATTLE_CORE=1']

# Every compile target depends on the shared headers: the compile commands below are custom targets without
# depfiles, so a header edit would otherwise leave stale objects (e.g. a changed handler flag constant).
w2u_header_deps = run_command(
  'python3', '-c',
  'import glob, sys; root = sys.argv[1]; print("\\n".join(sorted(glob.glob(root + "/include/*.h") + glob.glob(root + "/src/**/*.h", recursive=True))))',
  meson.project_source_root(),
  check: true,
).stdout().strip().split('\n')
includes = [
    # Important libraries.
    '-I' + meson.project_source_root() / 'include' / 'extlib',
    '-I' + meson.project_source_root() / 'include' / 'NitroKernel',
    '-I' + meson.project_source_root() / 'include' / 'swan',
    '-I' + meson.project_source_root() / 'include',

    # Custom code patches.
    '-I' + meson.project_source_root() / 'src' / 'pokedex_expansion',
    '-I' + meson.project_source_root() / 'src' / 'type_expansion',
    '-I' + meson.project_source_root() / 'src' / 'pwan_animation',
    '-I' + meson.project_source_root() / 'src' / 'pokeweb_gameplay',
]

sources = [
    pokedex_expansion,
    type_expansion,
    pokeweb_gameplay,
    files('../include/util/filesystem.cpp'),
    files('w2anim/w2u_anim_streams.cpp'),   # animated sprites (replaces the PWAN runtimes, Phase 4)
    files('battle_setup_patch.s'),
    files('battle_log/w2u_battle_log_save_patch.s'),
]

w2u_nonresident_modules = [
  {
    'name': 'w2u_field',
    'sources': pokeweb_field,
    'overlays': ['165'],
  },
  {
    'name': 'w2u_pokedex_ui',
    'sources': pokedex_nonbattle,
    'overlays': ['299', '302'],
  },
  {
    'name': 'w2u_menu_ui',
    'sources': [type_nonbattle, pokeweb_ui],
    'overlays': ['255', '265', '207'],
  },
  {
    'name': 'w2u_battle_log',
    'sources': battle_log,
    'overlays': ['167'],
  },
  {
    'name': 'w2u_pk5_battle_counters',
    'sources': files('battle_log/w2u_pk5_battle_counters.cpp'),
    'overlays': ['167'],
  },
  {
    'name': 'w2u_battle_log_summary',
    'sources': battle_log_summary,
    'overlays': ['207'],
  },
]

w2u_main_elf = custom_target(
  'w2u_main.elf',
  input: sources,
  depend_files: [files(
    'pokeweb_gameplay/w2u_terrain_texture_mappings.inc',
    'pokeweb_gameplay/w2u_battle_module_api_entries.inc',
  ), w2u_header_deps],
  output: 'w2u_main.elf',
  command: ['arm-none-eabi-g++', w2u_cpp_args, includes ,'-o', '@OUTPUT@', '@INPUT@'],
)

w2u_main_dll = custom_target(
  'w2u_main.dll',
  input: w2u_main_elf,
  output: 'w2u_main.dll',
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_import_verifier,
  ] + checked_rpm_depend_files,
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    strip_verifier="$5"
    strip_flag="$6"
    checked_packager="$7"
    import_verifier="$8"

    # The ESDB maps __aeabi_uidivmod / __aeabi_idivmod but not the plain division helpers: a call to one stays a
    # branch to itself after relocation (an endless loop at run time). -Os emits them even for constant divisors.
    if arm-none-eabi-nm -u "$input" | grep -E ' __aeabi_u?idiv$'; then
      echo "[!] w2u_main imports a division helper PMC cannot resolve (use u64 division or a multiply)." >&2
      exit 1
    fi
    python3 "$import_verifier" "$input" --esdb "$esdb"

    set -- python3 "$checked_packager" --jar "$ctrmap" --output "$output" -- -i "$input" --fourcc DLXF --esdb "$esdb" --generate-relocations
    if [ "$strip_flag" = '--strip' ]; then
      set -- "$@" --strip
    fi
    "$@"

    if [ "$strip_flag" = '--strip' ]; then
      python3 "$strip_verifier" "$output"
    fi
  ''',
    'package_w2u_main',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
    checked_rpm_packager,
    rpm_import_verifier,
  ],
)

w2u_battle_registry = meson.project_source_root() / 'src' / 'pokeweb_gameplay' / 'battle_modules' / 'registry.json'
w2u_battle_registry_generated = meson.project_source_root() / 'src' / 'pokeweb_gameplay' / 'w2u_battle_module_registry.inc'
w2u_battle_api_generated = meson.project_source_root() / 'src' / 'pokeweb_gameplay' / 'w2u_battle_module_api_entries.inc'
w2u_battle_meson_generated = meson.project_source_root() / 'src' / 'pokeweb_gameplay' / 'battle_modules' / 'meson.build'
w2u_battle_registry_generator = meson.project_source_root() / 'tools' / 'generate_w2u_battle_registry.py'
w2u_battle_registry_check = custom_target(
  'verify_w2u_battle_registry',
  input: [
    w2u_battle_registry,
    w2u_battle_registry_generated,
    files('pokeweb_gameplay/w2u_abilities.cpp'),
    files('pokeweb_gameplay/w2u_moves.cpp'),
    files('pokeweb_gameplay/w2u_items.cpp'),
    files('pokeweb_gameplay/w2u_field_effects.cpp'),
    w2u_battle_api_generated,
    w2u_battle_meson_generated,
    files('pokeweb_gameplay/w2u_strong_weather.cpp'),
  ],
  output: 'verify_w2u_battle_registry.stamp',
  depend_files: [w2u_battle_registry_generator],
  command: [
    'python3', w2u_battle_registry_generator,
    '--registry', '@INPUT0@',
    '--check', '@INPUT1@',
    '--source', '@INPUT2@',
    '--source', '@INPUT3@',
    '--source', '@INPUT4@',
    '--source', '@INPUT5@',
    '--api-check', '@INPUT6@',
    '--meson-check', '@INPUT7@',
    '--meson', '@INPUT7@',
    '--source', '@INPUT8@',
    '--stamp', '@OUTPUT@',
  ],
)

w2u_battle_module_dlls = []
w2u_battle_module_elfs = []
foreach battle_module : w2u_battle_module_definitions
  module_id = battle_module['id']
  module_slug = battle_module['slug']
  module_elf = custom_target(
    'w2u_battle_' + module_slug + '.elf',
    input: battle_module['sources'],
    output: 'w2u_battle_' + module_slug + '.elf',
    depend_files: [w2u_battle_api_generated, w2u_header_deps],
    command: ['sh', '-eu', '-c', '''
      output="$1"
      root="$2"
      module_id="$3"
      shift 3

      objdir="${output}.objs"
      rm -rf "$objdir"
      mkdir -p "$objdir"
      objects=""
      object_index=0

      for input in "$@"; do
        base="$(basename "$input")"
        obj="$objdir/${object_index}_${base%.*}.o"
        arm-none-eabi-g++ -mthumb -march=armv5t -mno-thumb-interwork -mno-long-calls -Os -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables -nostdinc++ -fvisibility=hidden -ffunction-sections -fdata-sections -DW2U_ENABLE_GEN6_BATTLE_ITEMS=1 -DW2U_BATTLE_CHILD=1 -DW2U_BATTLE_MODULE_ID="$module_id" -I"$root/include/extlib" -I"$root/include/NitroKernel" -I"$root/include/swan" -I"$root/include" -I"$root/src/pokeweb_gameplay" -c "$input" -o "$obj"
        objects="$objects $obj"
        object_index=$((object_index + 1))
      done

      raw="${output}.raw"
      localized="${output}.localized"
      arm-none-eabi-ld -r --gc-sections -u W2U_GetBattleModuleApi -o "$raw" $objects
      arm-none-eabi-objcopy --localize-hidden "$raw" "$localized"
      arm-none-eabi-objcopy --strip-unneeded "$localized" "$output"
      rm -f "$raw" "$localized"
    ''',
      'build_w2u_battle_' + module_slug,
      '@OUTPUT@',
      meson.project_source_root(),
      module_id.to_string(),
      '@INPUT@',
    ],
  )

  module_dll = custom_target(
    'w2u_battle_' + module_slug + '.dll',
    input: [module_elf, w2u_main_elf],
    output: 'w2u_battle_' + module_slug + '.dll',
    depend_files: [
      meson.project_source_root() / 'pmc' / 'IRDO.yml',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      meson.project_source_root() / 'tools' / 'restrict_w2u_battle_exports.py',
      meson.project_source_root() / 'tools' / 'verify_w2u_battle_module.py',
      rpm_import_verifier,
    ] + checked_rpm_depend_files,
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      core="$3"
      output="$4"
      esdb="$5"
      strip_verifier="$6"
      export_restrictor="$7"
      module_verifier="$8"
      checked_packager="$9"
      import_verifier="${10}"
      imports="${output%.dll}.core-imports.txt"
      exports="${output%.dll}.core-exports.txt"

      api_exports="$(arm-none-eabi-readelf -Ws "$input" | awk '$4 == "FUNC" && $5 == "GLOBAL" && $6 == "DEFAULT" && $8 == "W2U_GetBattleModuleApi" { count++ } END { print count + 0 }')"
      if [ "$api_exports" -ne 1 ]; then
        echo "[!] $input must expose exactly one default-visible module API." >&2
        exit 1
      fi
      if arm-none-eabi-nm --defined-only "$input" | grep -Eq 'THUMB_BRANCH|HOOK'; then
        echo "[!] $input retained a hook symbol." >&2
        exit 1
      fi

      arm-none-eabi-nm -u "$input" | awk '$2 ~ /^W2U_/ { print $2 }' > "$imports"
      arm-none-eabi-nm -g --defined-only "$core" | awk '$3 ~ /^W2U_/ { print $3 }' > "$exports"
      while IFS= read -r symbol; do
        if ! grep -Fqx "$symbol" "$exports"; then
          echo "[!] Battle child imports $symbol, but White2Upgrade.dll does not export it." >&2
          exit 1
        fi
      done < "$imports"
      python3 "$import_verifier" "$input" --esdb "$esdb" --core "$core"

      python3 "$checked_packager" --jar "$ctrmap" --output "$output" -- -i "$input" --fourcc DLXF --esdb "$esdb" --generate-relocations --strip
      python3 "$export_restrictor" "$output"
      python3 "$strip_verifier" "$output"
      python3 "$module_verifier" --elf "$input" --rpm "$output" --core "$core"
    ''',
      'package_w2u_battle_' + module_slug,
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      meson.project_source_root() / 'pmc' / 'IRDO.yml',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      meson.project_source_root() / 'tools' / 'restrict_w2u_battle_exports.py',
      meson.project_source_root() / 'tools' / 'verify_w2u_battle_module.py',
      checked_rpm_packager,
      rpm_import_verifier,
    ],
  )
  w2u_battle_module_elfs += [module_elf]
  w2u_battle_module_dlls += [module_dll]
endforeach

w2u_battle_linkage_command = [
  'python3',
  meson.project_source_root() / 'tools' / 'verify_w2u_battle_linkage.py',
  '--core', '@INPUT0@',
  '--pmc-symbols', meson.project_source_root() / 'pmc' / 'RPMSYM-PMC.rpm',
  '--esdb', meson.project_source_root() / 'pmc' / 'IRDO.yml',
  '--expected-count', w2u_battle_module_definitions.length().to_string(),
  '--stamp', '@OUTPUT@',
]
foreach module_index : range(w2u_battle_module_definitions.length())
  w2u_battle_linkage_command += [
    '--child',
    '@INPUT' + (module_index + 1).to_string() + '@',
  ]
endforeach
w2u_battle_linkage_check = custom_target(
  'verify_w2u_battle_linkage',
  input: [w2u_main_elf, w2u_battle_module_elfs],
  output: 'verify_w2u_battle_linkage.stamp',
  depends: w2u_battle_registry_check,
  depend_files: [
    meson.project_source_root() / 'tools' / 'verify_w2u_battle_linkage.py',
    meson.project_source_root() / 'pmc' / 'RPMSYM-PMC.rpm',
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
  ],
  command: w2u_battle_linkage_command,
)

w2u_battle_stage_command = [
  'python3',
  meson.project_source_root() / 'tools' / 'stage_w2u_battle_modules.py',
  '--registry',
  meson.project_source_root() / 'src' / 'pokeweb_gameplay' / 'battle_modules' / 'registry.json',
  '--stage-root',
  meson.project_source_root() / 'vfs' / 'data' / 'lib' / 'w2u_battle',
  '--stamp',
  '@OUTPUT@',
]
foreach module_index : range(w2u_battle_module_definitions.length())
  w2u_battle_stage_command += [
    '--module',
    module_index.to_string() + '=@INPUT' + module_index.to_string() + '@',
  ]
endforeach

w2u_battle_module_stage = custom_target(
  'stage_w2u_battle_modules',
  input: w2u_battle_module_dlls,
  output: 'stage_w2u_battle_modules.stamp',
  depends: [w2u_battle_registry_check, w2u_battle_linkage_check],
  build_always_stale: true,
  depend_files: [
    meson.project_source_root() / 'tools' / 'stage_w2u_battle_modules.py',
    w2u_battle_registry,
  ],
  command: w2u_battle_stage_command,
)

w2u_nonresident_dlls = []

foreach w2u_module : w2u_nonresident_modules
  w2u_name = w2u_module['name']
  w2u_expected_overlays = ','.join(w2u_module['overlays'])

  w2u_nonresident_elf = custom_target(
    w2u_name + '.elf',
    input: w2u_module['sources'],
    output: w2u_name + '.elf',
    depend_files: [battle_log_headers, w2u_header_deps],
    command: ['arm-none-eabi-g++', cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
  )

  w2u_nonresident_dll = custom_target(
    w2u_name + '.dll',
    input: [w2u_nonresident_elf, w2u_main_elf],
    output: w2u_name + '.dll',
    depend_files: [
      meson.project_source_root() / 'pmc' / 'IRDO.yml',
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      rpm_import_verifier,
    ],
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      core="$3"
      output="$4"
      esdb="$5"
      verifier="$6"
      expected_overlays="$7"
      strip_verifier="$8"
      strip_flag="$9"
      import_verifier="${10}"
      imports="${output%.dll}.w2u-imports.txt"
      exports="${output%.dll}.core-exports.txt"

      arm-none-eabi-nm -u "$input" | awk '$2 ~ /^W2U_/ { print $2 }' > "$imports"
      arm-none-eabi-nm -g --defined-only "$core" | awk '$3 ~ /^W2U_/ { print $3 }' > "$exports"
      while IFS= read -r symbol; do
        if ! grep -Fqx "$symbol" "$exports"; then
          echo "[!] Non-resident RPM imports $symbol, but the resident core does not export it." >&2
          exit 1
        fi
      done < "$imports"
      python3 "$import_verifier" "$input" --esdb "$esdb" --core "$core"

      set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
      if [ "$strip_flag" = '--strip' ]; then
        set -- "$@" --strip
      fi
      "$@"

      python3 "$verifier" "$output" --expect "$expected_overlays"
      if [ "$strip_flag" = '--strip' ]; then
        python3 "$strip_verifier" "$output"
      fi
    ''',
      'package_' + w2u_name,
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      meson.project_source_root() / 'pmc' / 'IRDO.yml',
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      w2u_expected_overlays,
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      rpm_strip_flag,
      rpm_import_verifier,
    ],
  )

  w2u_nonresident_dlls += [w2u_nonresident_dll]
endforeach

menu_evolution_w2_elf = custom_target(
  'MenuEvolutionW2.elf',
  input: menu_evolution_cpp,
  output: 'MenuEvolutionW2.elf',
  build_by_default: true,
  depend_files: [menu_evolution_headers, w2u_header_deps],
  command: ['arm-none-eabi-g++', cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
)

menu_evolution_w2_dll = custom_target(
  'MenuEvolutionW2.dll',
  input: menu_evolution_w2_elf,
  output: 'MenuEvolutionW2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'pmc' / 'menu_evolution_w2_meta.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_import_verifier,
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    nonresident_verifier="$5"
    strip_verifier="$6"
    meta="$7"
    import_verifier="$8"

    python3 "$import_verifier" "$input" --esdb "$esdb"
    "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta" --strip
    python3 "$nonresident_verifier" "$output" --expect '12,165,166'
    python3 "$strip_verifier" "$output"
  ''',
    'package_MenuEvolutionW2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    meson.project_source_root() / 'pmc' / 'menu_evolution_w2_meta.yml',
    rpm_import_verifier,
  ],
)

w2u_main_patch = custom_target(
  'stage_w2u_main_patch',
  input: [w2u_main_dll, w2u_nonresident_dlls, battle_log_save_guard_w2],
  output: 'stage_w2u_main_patch.stamp',
  build_always_stale: true,
  command: ['sh', '-eu', '-c', '''
    core="$1"
    field="$2"
    pokedex_ui="$3"
    menu_ui="$4"
    battle_log="$5"
    battle_counters="$6"
    battle_log_summary="$7"
    save_guard="$8"
    patch_dir="$9"
    stamp="${10}"

    mkdir -p "$patch_dir"
    rm -f "$patch_dir/White2UpgradeNonBattle.dll"
    cp "$core" "$patch_dir/White2Upgrade.dll"
    cp "$field" "$patch_dir/White2UpgradeField.dll"
    cp "$pokedex_ui" "$patch_dir/White2UpgradePokedex.dll"
    cp "$menu_ui" "$patch_dir/White2UpgradeUI.dll"
    cp "$battle_log" "$patch_dir/White2UpgradeBattleLog.dll"
    cp "$battle_counters" "$patch_dir/White2UpgradeBattleCounters.dll"
    cp "$battle_log_summary" "$patch_dir/White2UpgradeBattleLogSummary.dll"
    cp "$save_guard" "$patch_dir/BattleLogSaveGuardW2.dll"
    touch "$stamp"
  ''',
    'stage_w2u_main_patch',
    '@INPUT@',
    meson.project_source_root() / 'vfs' / 'data' / 'patches',
    '@OUTPUT@',
  ],
)

pwan_runtime_dlls = []

foreach pwan_module : pwan_runtime_modules
  pwan_name = pwan_module['name']
  pwan_expected_overlays = ','.join(pwan_module['overlays'])

  pwan_runtime_elf = custom_target(
    pwan_name + '.elf',
    input: pwan_module['sources'],
    depend_files: [pwan_runtime_depend_files, w2u_header_deps],
    output: pwan_name + '.elf',
    command: ['sh', '-eu', '-c', '''
      output="$1"
      root="$2"
      shift 2

      objdir="${output}.objs"
      rm -rf "$objdir"
      mkdir -p "$objdir"

      cxx_flags="-mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables"
      cxx_includes="-I${root}/include -I${root}/include/swan -I${root}/include/NitroKernel -I${root}/src/pwan_animation"
      asm_flags="-mthumb -march=armv5t -r"
      objects=""

      for input in "$@"; do
        base="$(basename "$input")"
        obj="$objdir/${base%.*}.o"
        case "$input" in
          *.cpp)
            arm-none-eabi-g++ $cxx_flags $cxx_includes -c "$input" -o "$obj"
            ;;
          *.s)
            arm-none-eabi-as $asm_flags -c "$input" -o "$obj"
            ;;
          *)
            echo "unsupported PWAN runtime source: $input" >&2
            exit 1
            ;;
        esac
        objects="$objects $obj"
      done

      arm-none-eabi-ld -o "$output" -r $objects
    ''',
      'build_' + pwan_name,
      '@OUTPUT@',
      meson.project_source_root(),
      '@INPUT@',
    ],
  )

  pwan_runtime_dll = custom_target(
    pwan_name + '.dll',
    input: pwan_runtime_elf,
    output: pwan_name + '.dll',
    depend_files: [
      meson.project_source_root() / 'pmc' / 'IRDO.yml',
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      rpm_import_verifier,
    ],
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      output="$3"
      esdb="$4"
      verifier="$5"
      expected_overlays="$6"
      strip_verifier="$7"
      strip_flag="$8"
      import_verifier="$9"
      undefined="${output%.dll}.undefined.txt"

      arm-none-eabi-nm -u "$input" > "$undefined"
      if grep -E '__aeabi_uidiv|__aeabi_uidivmod' "$undefined"; then
        echo "[!] PWAN runtime emitted unsigned division helper imports." >&2
        exit 1
      fi
      python3 "$import_verifier" "$input" --esdb "$esdb"

      set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
      if [ "$strip_flag" = '--strip' ]; then
        set -- "$@" --strip
      fi
      "$@"

      python3 "$verifier" "$output" --expect "$expected_overlays"
      if [ "$strip_flag" = '--strip' ]; then
        python3 "$strip_verifier" "$output"
      fi
    ''',
      'package_' + pwan_name,
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      meson.project_source_root() / 'pmc' / 'IRDO.yml',
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      pwan_expected_overlays,
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      rpm_strip_flag,
      rpm_import_verifier,
    ],
  )

  pwan_runtime_dlls += [pwan_runtime_dll]
endforeach

pwan_runtime_patch = custom_target(
  'stage_pokeweb_pwan_runtime_patch',
  input: pwan_runtime_dlls,
  output: 'stage_pokeweb_pwan_runtime_patch.stamp',
  build_always_stale: true,
  command: ['sh', '-eu', '-c', '''
    summary="$1"
    battle="$2"
    misc="$3"
    trainer="$4"
    patch_dir="$5"
    stamp="$6"

    # White 2 animates its sprites with the resident w2anim runtime (src/w2anim, Phase 4 of
    # docs/megab2w2-integration.md): the PWAN DLLs are still built (Black 2 shares the sources) but no
    # longer staged, so PMC loads none of them (they held 46.5 KB of its heap in battle).
    : "$summary" "$battle" "$misc" "$trainer"
    mkdir -p "$patch_dir"
    rm -f "$patch_dir/PokewebPwanW2.dll" "$patch_dir/PokewebPwanSummaryW2.dll" "$patch_dir/PokewebPwanBattleW2.dll"       "$patch_dir/PokewebPwanMiscW2.dll" "$patch_dir/PokewebPwanTrainerW2.dll"
    touch "$stamp"
  ''',
    'stage_pokeweb_pwan_runtime_patch',
    '@INPUT@',
    meson.project_source_root() / 'vfs' / 'data' / 'patches',
    '@OUTPUT@',
  ],
)

w2u_battle_heap_audit_command = [
  'python3',
  meson.project_source_root() / 'tools' / 'audit_white2upgrade_battle_heap.py',
  '--core', '@INPUT0@',
  '--battle-log', '@INPUT1@',
  '--battle-counters', '@INPUT2@',
  '--registry', w2u_battle_registry,
  '--baseline', meson.project_source_root() / 'pmc' / 'white2upgrade_battle_heap_baseline.json',
  '--output', '@OUTPUT@',
]
foreach module_index : range(w2u_battle_module_definitions.length())
  w2u_battle_heap_audit_command += [
    '--module',
    '@INPUT' + (module_index + 3).to_string() + '@',
  ]
endforeach
# The ROM depends on the audit: a build whose modules could not all fit the PMC heap fails instead of freezing a battle.
# Only the 12 KiB headroom is fatal; the savings-vs-monolith checks (`--enforce`, formerly on with strip_rpms) are
# warnings, since the integration core is larger than the monolithic baseline they compare against.
w2u_battle_heap_audit_command += ['--enforce-headroom']

w2u_battle_heap_audit = custom_target(
  'white2upgrade-battle-heap-audit',
  input: [
    w2u_main_dll,
    w2u_nonresident_dlls[3],
    w2u_nonresident_dlls[4],
    w2u_battle_module_dlls,
  ],
  output: 'white2upgrade-battle-heap-audit.json',
  depend_files: [
    meson.project_source_root() / 'tools' / 'audit_white2upgrade_battle_heap.py',
    w2u_battle_registry,
    meson.project_source_root() / 'pmc' / 'white2upgrade_battle_heap_baseline.json',
  ],
  command: w2u_battle_heap_audit_command,
)

# The stock Black 2 PWAN runtime is intentionally independent from the three
# White 2 targets above.  It reuses the battle implementation at build time,
# substituting only the three code-layout addresses that differ between the US
# B2 and W2 binaries, and links against a dedicated B2 hook table and ESDB.
pwan_battle_b2_elf = custom_target(
  'PokewebPwanBattleB2.elf',
  input: pwan_battle_b2_sources,
  depend_files: [pwan_runtime_depend_files, w2u_header_deps],
  output: 'PokewebPwanBattleB2.elf',
  build_by_default: true,
  command: ['sh', '-eu', '-c', '''
    output="$1"
    root="$2"
    shift 2

    objdir="${output}.objs"
    rm -rf "$objdir"
    mkdir -p "$objdir"

    cxx_flags="-mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables"
    cxx_includes="-I${root}/include -I${root}/include/swan -I${root}/include/NitroKernel -I${root}/src/pwan_animation"
    asm_flags="-mthumb -march=armv5t -r"
    objects=""

    for input in "$@"; do
      base="$(basename "$input")"
      obj="$objdir/${base%.*}.o"
      compile_input="$input"
      if [ "$base" = 'w2u_battle_anim.cpp' ]; then
        compile_input="$objdir/b2_battle_anim.cpp"
        sed -e 's/0x021F4280/0x021F4240/g' -e 's/0x021E97D5/0x021E9795/g' -e 's/0x021E7FBD/0x021E7F7D/g' "$input" > "$compile_input"
      fi
      case "$input" in
        *.cpp)
          arm-none-eabi-g++ $cxx_flags $cxx_includes -c "$compile_input" -o "$obj"
          ;;
        *.s)
          arm-none-eabi-as $asm_flags -c "$input" -o "$obj"
          ;;
        *)
          echo "unsupported Black 2 PWAN runtime source: $input" >&2
          exit 1
          ;;
      esac
      objects="$objects $obj"
    done

    arm-none-eabi-ld -o "$output" -r $objects
  ''',
    'build_PokewebPwanBattleB2',
    '@OUTPUT@',
    meson.project_source_root(),
    '@INPUT@',
  ],
)

pwan_battle_b2_dll = custom_target(
  'PokewebPwanBattleB2.dll',
  input: pwan_battle_b2_elf,
  output: 'PokewebPwanBattleB2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    verifier="$5"
    strip_verifier="$6"
    strip_flag="$7"
    undefined="${output%.dll}.undefined.txt"

    arm-none-eabi-nm -u "$input" > "$undefined"
    if grep -E '__aeabi_uidiv|__aeabi_uidivmod' "$undefined"; then
      echo '[!] Black 2 PWAN runtime emitted unsigned division helper imports.' >&2
      exit 1
    fi

    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
    if [ "$strip_flag" = '--strip' ]; then
      set -- "$@" --strip
    fi
    "$@"

    python3 "$verifier" "$output" --expect '168,167'
    if [ "$strip_flag" = '--strip' ]; then
      python3 "$strip_verifier" "$output"
    fi
  ''',
    'package_PokewebPwanBattleB2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
  ],
)

pwan_trainer_b2_elf = custom_target(
  'PokewebPwanTrainerB2.elf',
  input: pwan_trainer_b2_sources,
  depend_files: [pwan_runtime_depend_files, w2u_header_deps],
  output: 'PokewebPwanTrainerB2.elf',
  build_by_default: true,
  command: ['sh', '-eu', '-c', '''
    output="$1"
    root="$2"
    shift 2
    objdir="${output}.objs"
    rm -rf "$objdir"
    mkdir -p "$objdir"
    cxx_flags="-mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables"
    cxx_includes="-I${root}/include -I${root}/include/swan -I${root}/include/NitroKernel -I${root}/src/pwan_animation"
    asm_flags="-mthumb -march=armv5t -r"
    objects=""
    for input in "$@"; do
      base="$(basename "$input")"
      obj="$objdir/${base%.*}.o"
      case "$input" in
        *.cpp) arm-none-eabi-g++ $cxx_flags $cxx_includes -c "$input" -o "$obj" ;;
        *.s) arm-none-eabi-as $asm_flags -c "$input" -o "$obj" ;;
        *) echo "unsupported Black 2 trainer PWAN source: $input" >&2; exit 1 ;;
      esac
      objects="$objects $obj"
    done
    arm-none-eabi-ld -o "$output" -r $objects
  ''',
    'build_PokewebPwanTrainerB2',
    '@OUTPUT@',
    meson.project_source_root(),
    '@INPUT@',
  ],
)

pwan_trainer_b2_dll = custom_target(
  'PokewebPwanTrainerB2.dll',
  input: pwan_trainer_b2_elf,
  output: 'PokewebPwanTrainerB2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    verifier="$5"
    strip_verifier="$6"
    strip_flag="$7"
    undefined="${output%.dll}.undefined.txt"
    arm-none-eabi-nm -u "$input" > "$undefined"
    if grep -E '__aeabi_uidiv|__aeabi_uidivmod' "$undefined"; then
      echo '[!] Black 2 trainer PWAN runtime emitted unsigned division helper imports.' >&2
      exit 1
    fi
    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
    if [ "$strip_flag" = '--strip' ]; then set -- "$@" --strip; fi
    "$@"
    python3 "$verifier" "$output" --expect '168'
    if [ "$strip_flag" = '--strip' ]; then python3 "$strip_verifier" "$output"; fi
  ''',
    'package_PokewebPwanTrainerB2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
  ],
)

pwan_summary_b2_elf = custom_target(
  'PokewebPwanSummaryB2.elf',
  input: pwan_summary_b2_sources,
  depend_files: [pwan_runtime_depend_files, w2u_header_deps],
  output: 'PokewebPwanSummaryB2.elf',
  build_by_default: true,
  command: ['sh', '-eu', '-c', '''
    output="$1"
    root="$2"
    shift 2

    objdir="${output}.objs"
    rm -rf "$objdir"
    mkdir -p "$objdir"

    cxx_flags="-mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables"
    cxx_includes="-I${root}/include -I${root}/include/swan -I${root}/include/NitroKernel -I${root}/src/pwan_animation"
    asm_flags="-mthumb -march=armv5t -r"
    objects=""

    for input in "$@"; do
      base="$(basename "$input")"
      obj="$objdir/${base%.*}.o"
      compile_input="$input"
      case "$input" in
        *.cpp)
          compile_input="$objdir/b2_${base}"
          sed -e 's/0x021B4DDD/0x021B4D9D/g' -e 's/0x0201CDB5/0x0201CD89/g' -e 's/0x0201ADA9/0x0201AD7D/g' -e 's/0x0201ADB9/0x0201AD8D/g' -e 's/0x0201AEF9/0x0201AECD/g' "$input" > "$compile_input"
          arm-none-eabi-g++ $cxx_flags $cxx_includes -c "$compile_input" -o "$obj"
          ;;
        *.s)
          arm-none-eabi-as $asm_flags -c "$input" -o "$obj"
          ;;
        *)
          echo "unsupported Black 2 PWAN summary source: $input" >&2
          exit 1
          ;;
      esac
      objects="$objects $obj"
    done

    arm-none-eabi-ld -o "$output" -r $objects
    if arm-none-eabi-objdump -dr "$output" | grep -Eiq '021b4ddd|0201cdb5|0201ada9|0201adb9|0201aef9|0204b7c1|02049acd|021b3ef9'; then
      echo '[!] Black 2 PWAN summary runtime retained a White 2 absolute address.' >&2
      exit 1
    fi
  ''',
    'build_PokewebPwanSummaryB2',
    '@OUTPUT@',
    meson.project_source_root(),
    '@INPUT@',
  ],
)

pwan_summary_b2_dll = custom_target(
  'PokewebPwanSummaryB2.dll',
  input: pwan_summary_b2_elf,
  output: 'PokewebPwanSummaryB2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    verifier="$5"
    strip_verifier="$6"
    strip_flag="$7"
    undefined="${output%.dll}.undefined.txt"

    arm-none-eabi-nm -u "$input" > "$undefined"
    if grep -E '__aeabi_uidiv|__aeabi_uidivmod' "$undefined"; then
      echo '[!] Black 2 PWAN summary runtime emitted unsigned division helper imports.' >&2
      exit 1
    fi

    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
    if [ "$strip_flag" = '--strip' ]; then
      set -- "$@" --strip
    fi
    "$@"

    python3 "$verifier" "$output" --expect '207'
    if [ "$strip_flag" = '--strip' ]; then
      python3 "$strip_verifier" "$output"
    fi
  ''',
    'package_PokewebPwanSummaryB2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
  ],
)

pwan_misc_b2_elf = custom_target(
  'PokewebPwanMiscB2.elf',
  input: pwan_misc_b2_sources,
  depend_files: [pwan_runtime_depend_files, w2u_header_deps],
  output: 'PokewebPwanMiscB2.elf',
  build_by_default: true,
  command: ['sh', '-eu', '-c', '''
    output="$1"
    root="$2"
    shift 2

    objdir="${output}.objs"
    rm -rf "$objdir"
    mkdir -p "$objdir"

    cxx_flags="-mthumb -mno-thumb-interwork -march=armv5t -mno-long-calls -Wall -Wextra -Os -fira-loop-pressure -fipa-pta -fno-exceptions -fno-rtti -fno-unwind-tables -fno-asynchronous-unwind-tables"
    cxx_includes="-I${root}/include -I${root}/include/swan -I${root}/include/NitroKernel -I${root}/src/pwan_animation"
    asm_flags="-mthumb -march=armv5t -r"
    objects=""

    for input in "$@"; do
      base="$(basename "$input")"
      obj="$objdir/${base%.*}.o"
      compile_input="$input"
      case "$input" in
        *.cpp)
          compile_input="$objdir/b2_${base}"
          sed -e 's/0x0201CD25/0x0201CCF9/g' -e 's/0x0201C071/0x0201C045/g' -e 's/0x0201C009/0x0201BFDD/g' -e 's/0x0201C179/0x0201C14D/g' -e 's/0x0201A8D5/0x0201A8A9/g' -e 's/0x02019B15/0x02019AE9/g' -e 's/0x02019C39/0x02019C0D/g' -e 's/0x0201AAAD/0x0201AA81/g' -e 's/0x0201ADA9/0x0201AD7D/g' -e 's/0x0201AEF9/0x0201AECD/g' -e 's/0x021E57A1/0x021E5761/g' -e 's/0x021E5801/0x021E57C1/g' -e 's/0x021E4BB9/0x021E4B79/g' -e 's/0x021DF335/0x021DF2F5/g' -e 's/0x021DE939/0x021DE8F9/g' "$input" > "$compile_input"
          arm-none-eabi-g++ $cxx_flags $cxx_includes -c "$compile_input" -o "$obj"
          ;;
        *.s)
          arm-none-eabi-as $asm_flags -c "$input" -o "$obj"
          ;;
        *)
          echo "unsupported Black 2 PWAN misc source: $input" >&2
          exit 1
          ;;
      esac
      objects="$objects $obj"
    done

    arm-none-eabi-ld -o "$output" -r $objects
    if arm-none-eabi-objdump -dr "$output" | grep -Eiq '0201cd25|0201c071|0201c009|0201c179|0201a8d5|02019b15|02019c39|0201aaad|0201ada9|0201aef9|021e57a1|021e5801|021e4bb9|021df335|021de939'; then
      echo '[!] Black 2 PWAN misc runtime retained a White 2 absolute address.' >&2
      exit 1
    fi
  ''',
    'build_PokewebPwanMiscB2',
    '@OUTPUT@',
    meson.project_source_root(),
    '@INPUT@',
  ],
)

pwan_misc_b2_dll = custom_target(
  'PokewebPwanMiscB2.dll',
  input: pwan_misc_b2_elf,
  output: 'PokewebPwanMiscB2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    verifier="$5"
    strip_verifier="$6"
    strip_flag="$7"
    undefined="${output%.dll}.undefined.txt"

    arm-none-eabi-nm -u "$input" > "$undefined"
    if grep -E '__aeabi_uidiv|__aeabi_uidivmod' "$undefined"; then
      echo '[!] Black 2 PWAN misc runtime emitted unsigned division helper imports.' >&2
      exit 1
    fi

    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
    if [ "$strip_flag" = '--strip' ]; then
      set -- "$@" --strip
    fi
    "$@"

    python3 "$verifier" "$output" --expect '298,284,307,265'
    if [ "$strip_flag" = '--strip' ]; then
      python3 "$strip_verifier" "$output"
    fi
  ''',
    'package_PokewebPwanMiscB2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
  ],
)

pwan_legacy_retired_elf = custom_target(
  'PokewebPwanLegacyRetiredW2.elf',
  input: files('pwan_animation/pwan_legacy_retired.s'),
  output: 'PokewebPwanLegacyRetiredW2.elf',
  build_by_default: true,
  command: ['arm-none-eabi-as', '-mthumb', '-march=armv5t', '-r', '-c', '@INPUT@', '-o', '@OUTPUT@'],
)

pwan_legacy_retired_dll = custom_target(
  'PokewebPwanLegacyRetiredW2.dll',
  input: pwan_legacy_retired_elf,
  output: 'PokewebPwanLegacyRetiredW2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_import_verifier,
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    strip_verifier="$5"
    strip_flag="$6"
    import_verifier="$7"

    python3 "$import_verifier" "$input" --esdb "$esdb"
    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
    if [ "$strip_flag" = '--strip' ]; then
      set -- "$@" --strip
    fi
    "$@"

    if [ "$strip_flag" = '--strip' ]; then
      python3 "$strip_verifier" "$output"
    fi
  ''',
    'package_PokewebPwanLegacyRetiredW2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
    rpm_import_verifier,
  ],
)

# ---------------------------------------------------------------------------
# Black2Upgrade V1
# ---------------------------------------------------------------------------
# These targets share the authored gameplay C++ with White2Upgrade, but use a
# separate compile definition, generated IREO hook assembly, and a canonical
# clean-US-B2 ESDB.  Nothing here stages into the White 2 VFS.

b2u_aliases = meson.project_source_root() / 'pmc' / 'black2upgrade_aliases.json'
b2u_esdb_generator = meson.project_source_root() / 'tools' / 'generate_black2upgrade_esdb.py'
b2u_asm_generator = meson.project_source_root() / 'tools' / 'generate_black2upgrade_asm.py'
b2u_elf_verifier = meson.project_source_root() / 'tools' / 'verify_black2upgrade_elf.py'
b2u_rpm_verifier = meson.project_source_root() / 'tools' / 'verify_black2upgrade_rpm.py'
b2u_core_meta = meson.project_source_root() / 'pmc' / 'black2upgrade_core_meta.yml'
b2u_companion_meta = meson.project_source_root() / 'pmc' / 'black2upgrade_companion_meta.yml'

b2u_esdb = custom_target(
  'Black2Upgrade-IREO.yml',
  input: [
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'pmc' / 'IREO.yml',
    b2u_aliases,
  ],
  output: 'Black2Upgrade-IREO.yml',
  depend_files: b2u_esdb_generator,
  command: [
    'python3', b2u_esdb_generator,
    '--white-esdb', '@INPUT0@',
    '--ireo-esdb', '@INPUT1@',
    '--aliases', '@INPUT2@',
    '--output', '@OUTPUT@',
  ],
)

b2u_main_asm_inputs = [
  files('battle_setup_patch.s'),
  files('pokedex_expansion/Expansion_LimitAdjust.s'),
  files('type_expansion/Fairy_BattleLimitAdjust.s'),
  files('pokeweb_gameplay/w2u_mega_hooks.s'),
  files('pokeweb_gameplay/w2u_move_animation_hooks.s'),
  files('pokeweb_gameplay/w2u_transform_hooks.s'),
  files('pokeweb_gameplay/w2u_damage_hooks.s'),
  files('pokeweb_gameplay/w2u_terrain_indicator_hooks.s'),
  files('pokeweb_gameplay/w2u_terrain_texture_hooks.s'),
]
b2u_field_asm_inputs = [files('pokeweb_gameplay/w2u_field_item_hooks.s')]
b2u_pokedex_asm_inputs = [files('pokedex_expansion/Expansion_NonBattleLimitAdjust.s')]
b2u_ui_asm_inputs = [
  files('type_expansion/Fairy_LimitAdjust.s'),
  files('pokeweb_gameplay/w2u_mega_summary_hooks.s'),
]

b2u_main_asm = []
foreach index : range(b2u_main_asm_inputs.length())
  source = b2u_main_asm_inputs[index]
  generated = custom_target(
    'b2u_main_hook_' + index.to_string(),
    input: source,
    output: 'b2u_main_hook_' + index.to_string() + '.s',
    depend_files: [b2u_asm_generator, b2u_aliases],
    command: ['python3', b2u_asm_generator, '--input', '@INPUT@', '--output', '@OUTPUT@', '--aliases', b2u_aliases],
  )
  b2u_main_asm += [generated]
endforeach

b2u_field_asm = custom_target(
  'b2u_field_hooks',
  input: b2u_field_asm_inputs,
  output: 'b2u_field_hooks.s',
  depend_files: [b2u_asm_generator, b2u_aliases],
  command: ['python3', b2u_asm_generator, '--input', '@INPUT@', '--output', '@OUTPUT@', '--aliases', b2u_aliases],
)
b2u_pokedex_asm = custom_target(
  'b2u_pokedex_hooks',
  input: b2u_pokedex_asm_inputs,
  output: 'b2u_pokedex_hooks.s',
  depend_files: [b2u_asm_generator, b2u_aliases],
  command: ['python3', b2u_asm_generator, '--input', '@INPUT@', '--output', '@OUTPUT@', '--aliases', b2u_aliases],
)
b2u_ui_asm = []
foreach index : range(b2u_ui_asm_inputs.length())
  source = b2u_ui_asm_inputs[index]
  generated = custom_target(
    'b2u_ui_hook_' + index.to_string(),
    input: source,
    output: 'b2u_ui_hook_' + index.to_string() + '.s',
    depend_files: [b2u_asm_generator, b2u_aliases],
    command: ['python3', b2u_asm_generator, '--input', '@INPUT@', '--output', '@OUTPUT@', '--aliases', b2u_aliases],
  )
  b2u_ui_asm += [generated]
endforeach

b2u_metadata = files('black2upgrade_metadata.cpp')
b2u_cpp_args = cpp_args + [
  '-DW2U_TARGET_B2=1',
  '-DW2U_BATTLE_STATIC_GROUPS=1',
]

b2u_battle_log_elf = custom_target(
  'Black2UpgradeBattleLog.elf',
  input: [battle_log_cpp, battle_log_trampolines],
  output: 'Black2UpgradeBattleLog.elf',
  depend_files: [battle_log_headers, w2u_header_deps],
  command: ['arm-none-eabi-g++', b2u_cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
)

b2u_battle_log_dll = custom_target(
  'Black2UpgradeBattleLog.dll',
  input: [b2u_battle_log_elf, b2u_esdb],
  output: 'Black2UpgradeBattleLog.dll',
  build_by_default: true,
  depend_files: [
    b2u_elf_verifier,
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    b2u_companion_meta,
    b2u_rpm_verifier,
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    esdb="$3"
    output="$4"
    elf_verifier="$5"
    nonresident_verifier="$6"
    strip_verifier="$7"
    strip_flag="$8"
    meta="$9"
    metadata_verifier="${10}"

    python3 "$elf_verifier" "$input" --esdb "$esdb"
    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta"
    if [ "$strip_flag" = '--strip' ]; then set -- "$@" --strip; fi
    "$@"
    python3 "$metadata_verifier" "$output" --priority 4
    python3 "$nonresident_verifier" "$output" --expect '167'
    if [ "$strip_flag" = '--strip' ]; then python3 "$strip_verifier" "$output"; fi
  ''',
    'package_Black2UpgradeBattleLog',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    b2u_elf_verifier,
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
    b2u_companion_meta,
    b2u_rpm_verifier,
  ],
)

b2u_battle_log_summary_elf = custom_target(
  'Black2UpgradeBattleLogSummary.elf',
  input: battle_log_summary_cpp,
  output: 'Black2UpgradeBattleLogSummary.elf',
  depend_files: [battle_log_headers, w2u_header_deps],
  command: ['arm-none-eabi-g++', b2u_cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
)

b2u_battle_log_summary_dll = custom_target(
  'Black2UpgradeBattleLogSummary.dll',
  input: [b2u_battle_log_summary_elf, b2u_esdb],
  output: 'Black2UpgradeBattleLogSummary.dll',
  build_by_default: true,
  depend_files: [
    b2u_elf_verifier,
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    b2u_companion_meta,
    b2u_rpm_verifier,
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    esdb="$3"
    output="$4"
    elf_verifier="$5"
    nonresident_verifier="$6"
    strip_verifier="$7"
    strip_flag="$8"
    meta="$9"
    metadata_verifier="${10}"

    python3 "$elf_verifier" "$input" --esdb "$esdb"
    set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta"
    if [ "$strip_flag" = '--strip' ]; then set -- "$@" --strip; fi
    "$@"
    python3 "$metadata_verifier" "$output" --priority 4
    python3 "$nonresident_verifier" "$output" --expect '207'
    if [ "$strip_flag" = '--strip' ]; then python3 "$strip_verifier" "$output"; fi
  ''',
    'package_Black2UpgradeBattleLogSummary',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    b2u_elf_verifier,
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
    b2u_companion_meta,
    b2u_rpm_verifier,
  ],
)

# Black/White 1 use the same authored logger with direct retail-address
# wrappers. Keeping these as ordinary overlay-scoped DLXF modules lets the
# Pokeweb installer reuse PMC now and leaves that loader available for later
# small QoL modules.
bw1_battle_log_esdb = meson.project_source_root() / 'pmc' / 'bw1_battle_log_esdb.yml'
bw1_battle_log_targets = [
  {
    'name': 'Black1',
    'define': '-DW2U_TARGET_B1=1',
    'meta': meson.project_source_root() / 'pmc' / 'black1_battle_log_meta.yml',
  },
  {
    'name': 'White1',
    'define': '-DW2U_TARGET_W1=1',
    'meta': meson.project_source_root() / 'pmc' / 'white1_battle_log_meta.yml',
  },
]

foreach target : bw1_battle_log_targets
  target_args = cpp_args + ['-DW2U_TARGET_BW1=1', target['define']]
  battle_elf_name = target['name'] + 'BattleLog.elf'
  battle_dll_name = target['name'] + 'BattleLog.dll'
  counter_elf_name = target['name'] + 'BattleCounters.elf'
  counter_dll_name = target['name'] + 'BattleCounters.dll'
  summary_elf_name = target['name'] + 'BattleLogSummary.elf'
  summary_dll_name = target['name'] + 'BattleLogSummary.dll'

  battle_elf = custom_target(
    battle_elf_name,
    input: [battle_log_cpp, battle_log_trampolines],
    output: battle_elf_name,
    depend_files: [battle_log_headers, w2u_header_deps],
    command: ['arm-none-eabi-g++', target_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
  )
  custom_target(
    battle_dll_name,
    input: [battle_elf, bw1_battle_log_esdb],
    output: battle_dll_name,
    build_by_default: true,
    depend_files: [target['meta'], meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py', meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py'],
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      esdb="$3"
      output="$4"
      meta="$5"
      nonresident="$6"
      stripped="$7"
      "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta" --strip
      python3 "$nonresident" "$output" --expect '93'
      python3 "$stripped" "$output"
    ''',
      'package_' + target['name'] + 'BattleLog',
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      target['meta'],
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    ],
  )

  counter_elf = custom_target(
    counter_elf_name,
    input: files('battle_log/w2u_pk5_battle_counters.cpp'),
    output: counter_elf_name,
    depend_files: [battle_log_headers, w2u_header_deps],
    command: ['arm-none-eabi-g++', target_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
  )
  custom_target(
    counter_dll_name,
    input: [counter_elf, bw1_battle_log_esdb],
    output: counter_dll_name,
    build_by_default: true,
    depend_files: [target['meta'], meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py', meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py'],
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      esdb="$3"
      output="$4"
      meta="$5"
      nonresident="$6"
      stripped="$7"
      "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta" --strip
      python3 "$nonresident" "$output" --expect '93'
      python3 "$stripped" "$output"
    ''',
      'package_' + target['name'] + 'BattleCounters',
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      target['meta'],
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    ],
  )

  summary_elf = custom_target(
    summary_elf_name,
    input: battle_log_summary_cpp,
    output: summary_elf_name,
    depend_files: [battle_log_headers, w2u_header_deps],
    command: ['arm-none-eabi-g++', target_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
  )
  custom_target(
    summary_dll_name,
    input: [summary_elf, bw1_battle_log_esdb],
    output: summary_dll_name,
    build_by_default: true,
    depend_files: [target['meta'], meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py', meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py'],
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      esdb="$3"
      output="$4"
      meta="$5"
      nonresident="$6"
      stripped="$7"
      "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta" --strip
      python3 "$nonresident" "$output" --expect '131'
      python3 "$stripped" "$output"
    ''',
      'package_' + target['name'] + 'BattleLogSummary',
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      target['meta'],
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    ],
  )
endforeach

b2u_main_sources = [
  files('pokedex_expansion/w2u_pokedex.cpp'),
  files('pokedex_expansion/w2u_pokegra.cpp'),
  files('type_expansion/type_effectiveness.cpp'),
  files('pokeweb_gameplay/w2u_abilities.cpp'),
  files('pokeweb_gameplay/w2u_battle_static_resolver.cpp'),
  files('pokeweb_gameplay/w2u_field_effects.cpp'),
  files('pokeweb_gameplay/w2u_items.cpp'),
  files('pokeweb_gameplay/w2u_mega.cpp'),
  files('pokeweb_gameplay/w2u_moves.cpp'),
  files('pokeweb_gameplay/w2u_terrain_indicator.cpp'),
  files('pokeweb_gameplay/w2u_terrain_texture.cpp'),
  files('../include/util/filesystem.cpp'),
  b2u_metadata,
  b2u_main_asm,
]

b2u_main_elf = custom_target(
  'Black2Upgrade.elf',
  input: b2u_main_sources,
  depend_files: [files(
    'pokeweb_gameplay/w2u_terrain_texture_mappings.inc',
    'pokeweb_gameplay/w2u_battle_module_registry.inc',
    'pokeweb_gameplay/w2u_battle_module_api_entries.inc',
  ), w2u_header_deps],
  output: 'Black2Upgrade.elf',
  command: ['arm-none-eabi-g++', b2u_cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
)

b2u_main_dll = custom_target(
  'Black2Upgrade.dll',
  input: [b2u_main_elf, b2u_esdb],
  output: 'Black2Upgrade.dll',
  build_by_default: true,
  depend_files: [b2u_elf_verifier, b2u_rpm_verifier, meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py', b2u_core_meta] + checked_rpm_depend_files,
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    esdb="$3"
    output="$4"
    verifier="$5"
    strip_verifier="$6"
    strip_flag="$7"
    meta="$8"
    rpm_verifier="$9"
    checked_packager="${10}"

    python3 "$verifier" "$input" --esdb "$esdb"
    set -- python3 "$checked_packager" --jar "$ctrmap" --output "$output" -- -i "$input" --fourcc DLXF --esdb "$esdb" --generate-relocations --meta "$meta"
    if [ "$strip_flag" = '--strip' ]; then set -- "$@" --strip; fi
    "$@"
    python3 "$rpm_verifier" "$output" --priority 1
    if [ "$strip_flag" = '--strip' ]; then python3 "$strip_verifier" "$output"; fi
  ''',
    'package_Black2Upgrade',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    b2u_elf_verifier,
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    rpm_strip_flag,
    b2u_core_meta,
    b2u_rpm_verifier,
    checked_rpm_packager,
  ],
)

b2u_nonresident_modules = [
  {
    'name': 'Black2UpgradeField',
    'sources': [files('pokeweb_gameplay/w2u_field_items.cpp'), b2u_metadata, b2u_field_asm],
    'overlays': ['165'],
  },
  {
    'name': 'Black2UpgradePokedex',
    'sources': [b2u_metadata, b2u_pokedex_asm],
    'overlays': ['299', '302'],
  },
  {
    'name': 'Black2UpgradeUI',
    'sources': [b2u_metadata, b2u_ui_asm],
    'overlays': ['255', '265', '207'],
  },
  {
    'name': 'Black2UpgradeBattleCounters',
    'sources': files('battle_log/w2u_pk5_battle_counters.cpp'),
    'overlays': ['167'],
  },
]

b2u_nonresident_elfs = []
b2u_nonresident_dlls = []
foreach module : b2u_nonresident_modules
  name = module['name']
  expected_overlays = ','.join(module['overlays'])
  elf = custom_target(
    name + '.elf',
    input: module['sources'],
    output: name + '.elf',
    depend_files: [battle_log_headers, w2u_header_deps],
    command: ['arm-none-eabi-g++', b2u_cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
  )
  dll = custom_target(
    name + '.dll',
    input: [elf, b2u_main_elf, b2u_esdb],
    output: name + '.dll',
    build_by_default: true,
    depend_files: [
      b2u_elf_verifier,
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      b2u_companion_meta,
      b2u_rpm_verifier,
    ],
    command: ['sh', '-eu', '-c', '''
      ctrmap="$1"
      input="$2"
      core="$3"
      esdb="$4"
      output="$5"
      elf_verifier="$6"
      rpm_verifier="$7"
      expected_overlays="$8"
      strip_verifier="$9"
      strip_flag="${10}"
      meta="${11}"
      metadata_verifier="${12}"
      imports="${output%.dll}.core-imports.txt"
      exports="${output%.dll}.core-exports.txt"

      python3 "$elf_verifier" "$input" --esdb "$esdb" --allow-core-imports
      arm-none-eabi-nm -u "$input" | awk '$2 ~ /^W2U_/ { print $2 }' > "$imports"
      arm-none-eabi-nm -g --defined-only "$core" | awk '$3 ~ /^W2U_/ { print $3 }' > "$exports"
      while IFS= read -r symbol; do
        if ! grep -Fqx "$symbol" "$exports"; then
          echo "[!] $input imports $symbol, but Black2Upgrade.dll does not export it." >&2
          exit 1
        fi
      done < "$imports"

      set -- "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta"
      if [ "$strip_flag" = '--strip' ]; then set -- "$@" --strip; fi
      "$@"
      python3 "$metadata_verifier" "$output" --priority 4
      python3 "$rpm_verifier" "$output" --expect "$expected_overlays"
      if [ "$strip_flag" = '--strip' ]; then python3 "$strip_verifier" "$output"; fi
    ''',
      'package_' + name,
      ctrmap_jar,
      '@INPUT@',
      '@OUTPUT@',
      b2u_elf_verifier,
      meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
      expected_overlays,
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
      rpm_strip_flag,
      b2u_companion_meta,
      b2u_rpm_verifier,
    ],
  )
  b2u_nonresident_elfs += [elf]
  b2u_nonresident_dlls += [dll]
endforeach

menu_evolution_b2_elf = custom_target(
  'MenuEvolutionB2.elf',
  input: menu_evolution_cpp,
  output: 'MenuEvolutionB2.elf',
  build_by_default: true,
  depend_files: [menu_evolution_headers, w2u_header_deps],
  command: ['arm-none-eabi-g++', b2u_cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
)

menu_evolution_b2_dll = custom_target(
  'MenuEvolutionB2.dll',
  input: [menu_evolution_b2_elf, b2u_esdb],
  output: 'MenuEvolutionB2.dll',
  build_by_default: true,
  depend_files: [
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    meson.project_source_root() / 'pmc' / 'menu_evolution_b2_meta.yml',
  ],
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    esdb="$3"
    output="$4"
    nonresident_verifier="$5"
    strip_verifier="$6"
    meta="$7"

    "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations --meta "$meta" --strip
    python3 "$nonresident_verifier" "$output" --expect '12,165,166'
    python3 "$strip_verifier" "$output"
  ''',
    'package_MenuEvolutionB2',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'tools' / 'rpm_verify_nonresident.py',
    meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py',
    meson.project_source_root() / 'pmc' / 'menu_evolution_b2_meta.yml',
  ],
)

b2u_compat_generator = meson.project_source_root() / 'tools' / 'generate_black2upgrade_compatibility.py'
b2u_platform_header = meson.project_source_root() / 'include' / 'w2u_platform.h'
b2u_base_rom = meson.project_source_root() / get_option('black2_base_rom')
b2u_compat_asm_inputs = b2u_main_asm_inputs + b2u_field_asm_inputs + b2u_pokedex_asm_inputs + b2u_ui_asm_inputs
b2u_compat_command = [
  'python3', b2u_compat_generator,
  '--rom', '@INPUT0@',
  '--elf', '@INPUT1@',
  '--elf', '@INPUT2@',
  '--elf', '@INPUT3@',
  '--elf', '@INPUT4@',
  '--elf', '@INPUT5@',
  '--esdb', '@INPUT6@',
  '--aliases', '@INPUT7@',
  '--platform-header', '@INPUT8@',
  '--output', '@OUTPUT@',
]
foreach source : b2u_compat_asm_inputs
  b2u_compat_command += ['--asm', source]
endforeach

b2u_compatibility_manifest = custom_target(
  'black2upgrade-compatibility.json',
  input: [
    b2u_base_rom,
    b2u_main_elf,
    b2u_nonresident_elfs,
    b2u_esdb,
    b2u_aliases,
    b2u_platform_header,
  ],
  output: 'black2upgrade-compatibility.json',
  depend_files: [b2u_compat_generator, b2u_compat_asm_inputs],
  command: b2u_compat_command,
)

b2u_heap_audit = custom_target(
  'black2upgrade-heap-audit',
  input: [b2u_main_elf, pwan_battle_b2_elf, b2u_nonresident_elfs[2]],
  output: 'black2upgrade-heap-audit.json',
  depend_files: meson.project_source_root() / 'tools' / 'audit_black2upgrade_heap.py',
  command: [
    'python3', meson.project_source_root() / 'tools' / 'audit_black2upgrade_heap.py',
    '--core', '@INPUT0@',
    '--pwan-battle', '@INPUT1@',
    '--ui', '@INPUT2@',
    '--output', '@OUTPUT@',
  ],
)

b2u_w2_hash_guard = custom_target(
  'black2upgrade-white2-hash-guard',
  # The baseline predates the optional battle-log pair and intentionally
  # covers only the core and the original three nonresident companions.
  input: [
    w2u_main_dll,
    w2u_nonresident_dlls[0],
    w2u_nonresident_dlls[1],
    w2u_nonresident_dlls[2],
  ],
  output: 'black2upgrade-white2-hash-guard.json',
  depend_files: [
    meson.project_source_root() / 'tools' / 'verify_white2upgrade_hashes.py',
    meson.project_source_root() / 'pmc' / 'white2upgrade_b2_port_baseline.json',
  ],
  command: [
    'python3', meson.project_source_root() / 'tools' / 'verify_white2upgrade_hashes.py',
    '--expected', meson.project_source_root() / 'pmc' / 'white2upgrade_b2_port_baseline.json',
    '--output', '@OUTPUT@',
    '@INPUT@',
  ],
)

b2u_artifacts = custom_target(
  'stage_black2upgrade_artifacts',
  # Only the original field/Pokedex/UI modules are published as part of the
  # monolithic Black2Upgrade artifact set. The optional counter companion is
  # consumed by the standalone battle-log installer through its own target.
  input: [
    b2u_main_dll,
    b2u_nonresident_dlls[0],
    b2u_nonresident_dlls[1],
    b2u_nonresident_dlls[2],
    b2u_compatibility_manifest,
    b2u_heap_audit,
  ],
  output: 'black2upgrade-artifacts.stamp',
  build_by_default: true,
  depends: b2u_w2_hash_guard,
  command: ['sh', '-eu', '-c', '''
    core="$1"
    field="$2"
    pokedex="$3"
    ui="$4"
    compatibility="$5"
    heap_audit="$6"
    out_dir="$7"
    stamp="$8"
    mkdir -p "$out_dir"
    cp "$core" "$out_dir/Black2Upgrade.dll"
    cp "$field" "$out_dir/Black2UpgradeField.dll"
    cp "$pokedex" "$out_dir/Black2UpgradePokedex.dll"
    cp "$ui" "$out_dir/Black2UpgradeUI.dll"
    cp "$compatibility" "$out_dir/black2upgrade-compatibility.json"
    cp "$heap_audit" "$out_dir/black2upgrade-heap-audit.json"
    touch "$stamp"
  ''',
    'stage_black2upgrade_artifacts',
    '@INPUT@',
    meson.project_build_root() / 'black2upgrade-artifacts',
    '@OUTPUT@',
  ],
)
