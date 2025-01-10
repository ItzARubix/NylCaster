project('FeedTheBeast', 'cpp')
useSystemSFML = get_option('useSystemSFML')

if useSystemSFML
  sfmldep = dependency('sfml-all')
  executable('FeedTheBeast', 'main.cpp', dependencies : sfmldep)
else
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
endif
