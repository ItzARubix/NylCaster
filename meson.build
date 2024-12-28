project('FeedTheBeast', 'cpp', default_options : ['cpp_std=c++17'])

cmake = import('cmake')
sfml_proj = cmake.subproject('sfml')
sfml_graphics = sfml_proj.dependency('sfml-graphics')
sfml_window = sfml_proj.dependency('sfml-window')
sfml_system = sfml_proj.dependency('sfml-system')

if build_machine.system() == 'windows'
    compiler = meson.get_compiler('cpp')
    winmm = compiler.find_library('winmm', required: true)
    ogl = compiler.find_library('opengl32', required: true)
    sfml_main = sfml_proj.dependency('sfml-main')
    executable('FeedTheBeast', 'main.cpp', dependencies : [sfml_graphics, sfml_window, sfml_system, sfml_main, winmm, ogl], win_subsystem: 'console')
else
    executable('FeedTheBeast', 'main.cpp', dependencies : [sfml_graphics, sfml_window, sfml_system])
endif
