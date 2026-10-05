vfs_files = []
vfs_build_dir = meson.project_build_root() / 'vfs' / 'data'
relative_source_root = fs.relative_to(meson.project_source_root(), meson.project_build_root())
gen5_text_py = find_program(meson.project_source_root() / 'tools' / 'text' / 'gen5_text.py', native: true)
w2anim_streams_py = find_program(meson.project_source_root() / 'tools' / 'w2anim' / 'build_w2anim_streams.py', native: true)
double_battle_fix_py = find_program(meson.project_source_root() / 'tools' / 'stage_double_battle_fix.py', native: true)

double_battle_fix = custom_target(
  'stage_double_battle_fix_w2',
  input: [
    meson.project_source_root() / '..' / 'IRDO_Extracted' / 'overlay' / 'overlay_0036.bin',
    meson.project_source_root() / 'vfs' / 'y9.bin',
  ],
  output: 'stage_double_battle_fix_w2.stamp',
  command: [
    double_battle_fix_py,
    '--base-overlay', '@INPUT0@',
    '--overlay-table', '@INPUT1@',
    '--output', meson.project_source_root() / 'vfs' / 'data' / 'patches' / 'DoubleBattleFixW2.dll',
    '--stamp', '@OUTPUT@',
  ],
  # This also revalidates that no other patch has claimed either overlay hook.
  build_always_stale: true,
)

vfs_files += double_battle_fix

pwan_asset_list = run_command(
  'sh',
  '-c',
  'cd "$1" && find assets/pokeweb_pwan -maxdepth 1 -type f \( -name config.bin -o -name "*.pwan" \) | sort',
  'find_pwan_assets',
  meson.project_source_root(),
  check: true,
).stdout().strip()

pwan_assets = []
foreach pwan_asset : pwan_asset_list.split('\n')
  if pwan_asset != ''
    pwan_assets += meson.project_source_root() / pwan_asset
  endif
endforeach


sidecar_vfs_files = {
  'poke_form_list.bin': meson.current_source_dir() / 'pml' / 'poke_form_list.bin',
  'pokeicon_palette_map.bin': meson.current_source_dir() / 'pml' / 'pokeicon_palette_map.bin',
  'type_chart.bin': meson.current_source_dir() / 'pml' / 'types' / 'type_chart.bin',
  'type_palette_map.bin': meson.current_source_dir() / 'pml' / 'types' / 'type_palette_map.bin',
}

foreach sidecar_name, sidecar_source : sidecar_vfs_files
  vfs_files += custom_target(
    'stage_' + sidecar_name,
    input: sidecar_source,
    output: 'stage_' + sidecar_name + '.stamp',
    command: ['sh', '-c',
      'mkdir -p "$(dirname "$2")" && cp "$1" "$2" && touch "$3"',
      'stage_sidecar',
      '@INPUT@',
      meson.project_source_root() / 'vfs' / 'data' / sidecar_name,
      '@OUTPUT@'
    ],
  )
endforeach

# Load all of the resources.
subdir('encounters')
subdir('graphics')
subdir('items')
subdir('pml')
subdir('trainers')
subdir('text')

# Animated Pokemon sprites (D2, docs/megab2w2-integration.md Phase 4): the PWAN assets converted into w2anim streams for
# the resident runtime (src/w2anim). PWAN's NARC and runtime DLLs are no longer staged; an old staged NARC is removed.
w2anim_streams = custom_target(
  'build_w2anim_streams',
  input: pwan_assets,
  output: 'build_w2anim_streams.stamp',
  depends: [pokegra_battle_stage, personal_narc_stage],
  command: ['sh', '-eu', '-c', '''
    rm -f "$7/zz_pokeweb_pwan/pwan.narc"
    rmdir "$7/zz_pokeweb_pwan" 2>/dev/null || true
    python3 "$1" --pwan "$2" --pokegra "$3" --personal "$4" --output "$5" --cache "$6" --stamp "$8"
  ''',
    'build_w2anim_streams',
    w2anim_streams_py.full_path(),
    meson.project_source_root() / 'assets' / 'pokeweb_pwan',
    meson.project_source_root() / 'vfs' / 'data' / 'a' / '0' / '0' / '4',
    meson.project_source_root() / 'vfs' / 'data' / 'a' / '0' / '1' / '6',
    meson.project_source_root() / 'vfs' / 'data' / 'w2anim' / 'streams.bin',
    meson.current_build_dir() / 'w2anim_cache',
    meson.project_source_root() / 'vfs' / 'data',
    '@OUTPUT@',
  ],
  build_always_stale: true,
)

vfs_files += w2anim_streams

# System Text (/a/0/0/2)
system_text_arc = 'a' / '0' / '0' / '2'
system_text_files = []
foreach system_text_file : system_text
  if system_text_file != ''
    system_text_files += meson.current_source_dir() / 'text' / 'system' / (system_text_file + '.toml')
  endif
endforeach

vfs_files += custom_target(
  'build_system_text_narc',
  input: system_text_files,
  output: 'build_system_text_narc.stamp',
  command: [gen5_text_py, 'build-dir', meson.current_source_dir() / 'text' / 'system', meson.project_source_root() / 'vfs' / 'data' / system_text_arc, '--stamp', '@OUTPUT@'],
)

# Game/Map Text (/a/0/0/3)
game_text_arc = 'a' / '0' / '0' / '3'
game_text_files = []
foreach game_text_file : game_text
  if game_text_file != ''
    game_text_files += meson.current_source_dir() / 'text' / 'game' / (game_text_file + '.toml')
  endif
endforeach

vfs_files += custom_target(
  'build_game_text_narc',
  input: game_text_files,
  output: 'build_game_text_narc.stamp',
  command: [gen5_text_py, 'build-dir', meson.current_source_dir() / 'text' / 'game', meson.project_source_root() / 'vfs' / 'data' / game_text_arc, '--stamp', '@OUTPUT@'],
)

# pokegra/battle (/a/0/0/4)
# I don't know how I'm going to deal with this one...
