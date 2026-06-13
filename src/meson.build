patches = []

subdir('pokedex_expansion')
subdir('type_expansion')
subdir('pwan_animation')
subdir('pokeweb_gameplay')

cxx = meson.get_compiler('cpp')
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
    files('battle_setup_patch.s'),
]

w2u_main_elf = custom_target(
  'w2u_main.elf',
  input: sources,
  output: 'w2u_main.elf',
  command: ['arm-none-eabi-g++', cpp_args, includes ,'-o', '@OUTPUT@', '@INPUT@'],
)

w2u_main_dll = custom_target(
  'w2u_main.dll',
  input: w2u_main_elf,
  output: 'w2u_main.dll',
  command: ['sh', '-c',
        '"${JAVA:-java}" -cp "$1" rpm.cli.RPMTool -i "$2" --fourcc DLXF -o "$3" --esdb "$4" --generate-relocations',
        'rpmtool',
        ctrmap_jar,
        '@INPUT@',
        '@OUTPUT@',
        meson.project_source_root() / 'pmc' / 'IRDO.yml',
    ],
)

w2u_main_patch = custom_target(
  'stage_w2u_main_patch',
  input: w2u_main_dll,
  output: 'stage_w2u_main_patch.stamp',
  build_always_stale: true,
  command: ['sh', '-eu', '-c', '''
    input="$1"
    output="$2"
    stamp="$3"

    mkdir -p "$(dirname "$output")"
    cp "$input" "$output"
    touch "$stamp"
  ''',
    'stage_w2u_main_patch',
    '@INPUT@',
    meson.project_source_root() / 'vfs' / 'data' / 'patches' / 'w2u_main.dll',
    '@OUTPUT@',
  ],
)

pwan_runtime_elf = custom_target(
  'PokewebPwanW2.elf',
  input: pwan_runtime_sources,
  output: 'PokewebPwanW2.elf',
  command: ['arm-none-eabi-g++', cpp_args, includes, '-o', '@OUTPUT@', '@INPUT@'],
)

pwan_runtime_dll = custom_target(
  'PokewebPwanW2.dll',
  input: pwan_runtime_elf,
  output: 'PokewebPwanW2.dll',
  command: ['sh', '-eu', '-c', '''
    ctrmap="$1"
    input="$2"
    output="$3"
    esdb="$4"
    marker="$5"
    undefined="${output%.dll}.undefined.txt"

    arm-none-eabi-nm -u "$input" > "$undefined"
    if grep -E '__aeabi_uidiv|__aeabi_uidivmod' "$undefined"; then
      echo "[!] PWAN runtime emitted unsigned division helper imports." >&2
      exit 1
    fi

    "${JAVA:-java}" -cp "$ctrmap" rpm.cli.RPMTool -i "$input" --fourcc DLXF -o "$output" --esdb "$esdb" --generate-relocations
    python3 "$marker" "$output"
  ''',
    'pokeweb_pwan_runtime',
    ctrmap_jar,
    '@INPUT@',
    '@OUTPUT@',
    meson.project_source_root() / 'pmc' / 'IRDO.yml',
    meson.project_source_root() / 'tools' / 'pwan_mark_resident.py',
  ],
)

pwan_runtime_patch = custom_target(
  'stage_pokeweb_pwan_runtime_patch',
  input: pwan_runtime_dll,
  output: 'stage_pokeweb_pwan_runtime_patch.stamp',
  build_always_stale: true,
  command: ['sh', '-eu', '-c', '''
    input="$1"
    output="$2"
    stamp="$3"

    mkdir -p "$(dirname "$output")"
    cp "$input" "$output"
    touch "$stamp"
  ''',
    'stage_pokeweb_pwan_runtime_patch',
    '@INPUT@',
    meson.project_source_root() / 'vfs' / 'data' / 'patches' / 'PokewebPwanW2.dll',
    '@OUTPUT@',
  ],
)
