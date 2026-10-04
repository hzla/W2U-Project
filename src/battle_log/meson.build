battle_log_cpp = files('w2u_battle_log.cpp')
battle_log_summary_cpp = files('w2u_battle_log_summary.cpp')
battle_log_trampolines = files('w2u_battle_log_trampolines_pp.S')
battle_log_headers = files(
  '../../include/w2u_battle_log.h',
  '../../include/w2u_battle_log_attribution.h',
  '../../include/w2u_ko_move_pending.h',
)
menu_evolution_cpp = files(
  'w2u_menu_evolution.cpp',
  'w2u_menu_evolution_script_api.cpp',
)
menu_evolution_headers = files(
  '../../include/w2u_battle_log.h',
  '../../include/w2u_menu_evolution_logic.h',
  '../../include/w2u_menu_relearn_logic.h',
  '../../include/w2u_menu_evolution_script_api.h',
)

menu_evolution_logic_test = executable(
  'menu_evolution_logic_test',
  files('../../tools/test_menu_evolution_logic.cpp'),
  include_directories: incdir,
  native: true,
)
test('menu evolution record resolver', menu_evolution_logic_test)
menu_relearn_logic_test = executable(
  'menu_relearn_logic_test',
  files('../../tools/test_menu_relearn_logic.cpp'),
  include_directories: incdir,
  native: true,
)
test('menu relearn union and process routing', menu_relearn_logic_test)
ko_move_pending_test = executable(
  'ko_move_pending_test',
  files('../../tools/test_ko_move_pending.cpp'),
  include_directories: incdir,
  native: true,
)
test('KO move identity and learning sessions', ko_move_pending_test)
battle_log_attribution_test = executable(
  'battle_log_attribution_test',
  files('../../tools/test_battle_log_attribution.cpp'),
  include_directories: incdir,
  native: true,
)
test('battle log direct damage attribution', battle_log_attribution_test)
battle_log = [battle_log_cpp, battle_log_trampolines]
battle_log_summary = [battle_log_summary_cpp]
save_guard_test = executable('battle_log_save_guard_test',
  files('../../tools/test_battle_log_save_guard.cpp'), native: true)
test('battle log retail save isolation', save_guard_test)

# Three verified ARM9 entry replacements and one application-heap allocation.
# Keep this resident guard separate from the much larger battle-only modules.
foreach guard : [
  ['W2', 'bw2', '0x02039DC9'], ['B2', 'bw2', '0x02039D9D'],
  ['W', 'bw1', '0x020300B0'], ['B', 'bw1', '0x02030098'],
]
  guard_name = 'BattleLogSaveGuard' + guard[0]
  guard_args = cpp_args + ['-DGUARD_ALLOC_ADDRESS=' + guard[2], '-fno-builtin']
  guard_esdb = meson.project_source_root() / 'pmc' / ('battle_log_save_guard_' + guard[1] + '.yml')
  guard_elf = custom_target(guard_name + '.elf',
    input: files('w2u_battle_log_save_guard.cpp'), output: guard_name + '.elf',
    command: ['arm-none-eabi-g++', guard_args, '-o', '@OUTPUT@', '@INPUT@'])
  guard_dll = custom_target(guard_name + '.dll',
    input: guard_elf, output: guard_name + '.dll', depend_files: guard_esdb,
    command: ['sh', '-eu', '-c', '''
      "${JAVA:-java}" -cp "$1" rpm.cli.RPMTool -i "$2" --fourcc DLXF -o "$3" --esdb "$5" --generate-relocations --strip
      python3 "$4" "$3"
    ''', 'package_save_guard', ctrmap_jar, '@INPUT@', '@OUTPUT@',
      meson.project_source_root() / 'tools' / 'rpm_verify_stripped.py', guard_esdb])
  if guard[0] == 'W2'
    battle_log_save_guard_w2 = guard_dll
  endif
endforeach
