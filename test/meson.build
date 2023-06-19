catch2_proj = subproject('catch2')
catch2 = catch2_proj.get_variable('catch2_with_main_dep')

boost = dependency('boost')

exe = executable('tests',
                 'benchmark.cpp',
                 'test_vector_pair_sort.cpp',
                 'test_all.cpp',
                 include_directories: inc,
                 dependencies: [catch2, boost])

test('tests', exe, args: ['--skip-benchmarks', '--colour-mode=ansi'])
benchmark('tests', exe, timeout: 0, args: ['--colour-mode=ansi', '[!benchmark]', '--benchmark-no-analysis'])
