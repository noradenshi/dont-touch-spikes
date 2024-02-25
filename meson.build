project('dont-touch-spikes', 'c',
  default_options: [
    'prefix=/home/noradenshi/Projects/dont-touch-spikes',
    'c_std=c2x'
  ]
)

cc = meson.get_compiler('c')

deps = [ cc.find_library('raylib') ]

sources = files(
  'src/main.c',
  'src/bird.c',
  'src/spike.c',
) 

executable('exe', sources,
  include_directories: ['include'],
  dependencies: deps,
  install: true)
