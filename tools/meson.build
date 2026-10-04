python3_native = find_program('python3', native: true)
rom_layout_finalizer_py = meson.current_source_dir() / 'finalize_white2_rom.py'

run_target(
  'source-privacy-check',
  command: [python3_native, meson.current_source_dir() / 'check_source_privacy.py'],
  env: ['PYTHONDONTWRITEBYTECODE=1'],
)

test(
  'Portable report and artifact privacy',
  python3_native,
  args: [meson.current_source_dir() / 'tests' / 'test_source_privacy.py'],
  env: ['PYTHONDONTWRITEBYTECODE=1'],
)

test(
  'White 2 ROM layout finalizer',
  python3_native,
  args: [meson.current_source_dir() / 'tests' / 'test_finalize_white2_rom.py'],
)

test(
  'Substitute graphics layout',
  python3_native,
  args: [meson.current_source_dir() / 'tests' / 'test_substitute_graphics.py'],
)

subdir('CTRMap')
subdir('mkdata')
