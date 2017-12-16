#
#
#

cmake_minimum_required(VERSION 3.2)
project (octave_examples)

find_package(Qt5Widgets)

add_library(bzoctave STATIC bezierMk2.cc bezierMk2.h CoordinateTransformator.h CoordinateTransformator.cc Plotter.cc Plotter.h)
qt5_use_modules(bzoctave Widgets)

add_executable(plot_b6 plot_b6.cc)
target_link_libraries(plot_b6 bzoctave)

qt5_use_modules(plot_b6 Widgets)
set_target_properties(plot_b6 bzoctave PROPERTIES FOLDER "examples")

# end of file