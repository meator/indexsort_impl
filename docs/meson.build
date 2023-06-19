doxygen_exe = find_program('doxygen', required : false)

if doxygen_exe.found()
  cdata = configuration_data()
  cdata.set('TOP_BUILDDIR', meson.project_build_root())
  cdata.set('TOP_SRCDIR', meson.project_source_root())
  cdata.set('PROJECT_NAME', meson.project_name())

  doxyfile = configure_file(input: 'Doxyfile.in', output: 'Doxyfile', configuration: cdata)
  custom_target('docs', input: doxyfile, output: 'html', command: [doxygen_exe, doxyfile], console: true, build_always_stale: true)
else
  warning('Documentation disabled without doxygen.')
endif
