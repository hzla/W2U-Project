vfs_files = []
vfs_build_dir = meson.project_build_root() / 'vfs' / 'data'
relative_source_root = fs.relative_to(meson.project_source_root(), meson.project_build_root())
gen5_text_py = find_program(meson.project_source_root() / 'tools' / 'text' / 'gen5_text.py', native: true)
pwan_narc_py = find_program(meson.project_source_root() / 'tools' / 'pwan' / 'build_pwan_narc.py', native: true)

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

pwan_runtime_archive = custom_target(
  'build_pokeweb_pwan_narc',
  input: pwan_assets,
  output: 'build_pokeweb_pwan_narc.stamp',
  command: [
    pwan_narc_py,
    '--src', meson.project_source_root() / 'assets' / 'pokeweb_pwan',
    '--output', meson.project_source_root() / 'vfs' / 'data' / 'zz_pokeweb_pwan' / 'pwan.narc',
    '--stamp', '@OUTPUT@',
  ],
  build_always_stale: true,
)

vfs_files += pwan_runtime_archive

# Load all of the resources.
subdir('encounters')
subdir('graphics')
subdir('items')
subdir('pml')
subdir('trainers')
subdir('text')

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
