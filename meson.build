project('White2Upgrade', 'cpp', version: '0.0.1')

fs = import('fs')
incdir = include_directories('include')

cpp_args = [
    '-mthumb',
    '-march=armv5t',
    '-mno-thumb-interwork',
    '-mno-long-calls',
    '-r',
    '-nostdinc++',
    '-Os',
    '-fno-exceptions',
    '-fno-rtti',
    '-fno-unwind-tables',
    '-fno-asynchronous-unwind-tables',
    '-DW2U_ENABLE_GEN6_BATTLE_ITEMS=1'
]

asm_args = [
    '-mthumb',
    '-march=armv5t',
    '-r'
]

# Tools
subdir('tools')

# Custom code patches.  
subdir('src')

# Assets
subdir('data')

item_icon_patch_py = find_program(meson.project_source_root() / 'tools' / 'item_icons' / 'build_item_icon_patch.py', native: true)
patch_pmc_sysheap_py = find_program(meson.project_source_root() / 'tools' / 'patch_pmc_sysheap.py', native: true)
patch_arm9_footer_py = meson.project_source_root() / 'tools' / 'patch_arm9_footer.py'
main_menu_skip_patch = meson.project_source_root() / 'vfs' / 'data' / 'patches' / 'MainMenuSkip(1).dll'

item_icon_asset_list = run_command(
  'sh',
  '-c',
  'cd "$1" && find assets/item_icons -type f \( -name "*.png" -o -name "*.pal" \) | sort',
  'find_item_icon_assets',
  meson.project_source_root(),
  check: true,
).stdout().strip()

item_icon_assets = []
foreach item_icon_asset : item_icon_asset_list.split('\n')
  if item_icon_asset != ''
    item_icon_assets += meson.project_source_root() / item_icon_asset
  endif
endforeach

pmc_arm9 = custom_target(
  'pmc_arm9',
  input: meson.project_source_root() / 'pmc' / 'ARM9PMC.bin',
  depend_files: item_icon_assets,
  output: 'pmc_arm9.stamp',
  command: [
    item_icon_patch_py,
    '--arm9-input', '@INPUT@',
    '--arm9-output', meson.project_source_root() / 'vfs' / 'arm9.bin',
    '--vfs-output-dir', meson.project_source_root() / 'vfs' / 'data' / 'a' / '0' / '2' / '5',
    '--icons', meson.project_source_root() / 'assets' / 'item_icons' / 'icons',
    '--palettes', meson.project_source_root() / 'assets' / 'item_icons' / 'icon_palettes',
    '--base-icon-archive', meson.project_source_root() / '..' / 'IRDO_Extracted' / 'data' / 'a' / '0' / '2' / '5',
    '--report', meson.project_build_root() / 'item_icon_patch_report.json',
    '--stamp', '@OUTPUT@',
  ],
)

pmc_overlay = custom_target(
  'pmc_overlay',
  input: meson.project_source_root() / 'pmc' / 'OVL344.bin',
  output: 'pmc_overlay.stamp',
  command: [
    patch_pmc_sysheap_py,
    '--input', '@INPUT@',
    '--output', meson.project_source_root() / 'vfs' / 'overlay' / 'overlay_0344.bin',
    '--stamp', '@OUTPUT@',
  ],
)

pmc_symbols = custom_target(
  'pmc_symbols',
  input: meson.project_source_root() / 'pmc' / 'RPMSYM-PMC.rpm',
  output: 'pmc_symbols.stamp',
  command: ['sh', '-eu', '-c', '''
    input="$1"
    output="$2"
    stamp="$3"

    mkdir -p "$(dirname "$output")"
    cp "$input" "$output"
    touch "$stamp"
  ''',
    'stage_pmc_symbols',
    '@INPUT@',
    meson.project_source_root() / 'vfs' / 'data' / 'data' / 'codeinjection' / 'RPMSYM-PMC.rpm',
    '@OUTPUT@',
  ],
)
  
# The ROM itself
rom = custom_target('White2Upgrade.nds',
  output: 'White2Upgrade.nds',
  input: [
    vfs_files,
    w2u_main_patch,
    pwan_runtime_patch,
    main_menu_skip_patch,
    pmc_arm9,
    pmc_overlay,
    pmc_symbols
  ],
  command: ['sh', '-eu', '-c',
    '"${JAVA:-java}" -cp "$1" ctrmap.cli.ROMBuilder --input "$2" --output "$3"; python3 "$4" --rom "$3" --arm9 "$5"',
    'rombuilder',
    ctrmap_jar,
    meson.project_source_root() / 'White2Upgrade.cmproj',
    '@OUTPUT@',
    patch_arm9_footer_py,
    meson.project_source_root() / 'vfs' / 'arm9.bin',
  ],
)
