python3 = find_program('python3', native: true)
mkdata_py = [python3, meson.current_source_dir() / 'mkdata.py']
pack_narc_py = find_program('pack_narc.py', native: true)
# The serializers: data targets rebuild when one changes (depend_files: mkdata_deps)
mkdata_deps = files('mkdata.py', 'mkdata_util.py', 'impl/enc.py', 'impl/generic.py', 'impl/lz.py', 'impl/msg.py',
                    'impl/serializer.py', 'impl/trainer.py', 'impl/y9.py')
