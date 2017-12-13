#
#
#

project (octave_examples)

add_library(bzoctave STATIC bezierMk2.cc bezierMk2.h)
add_executable(plot_b6 plot_b6.cc)
target_link_libraries(plot_b6 bzoctave)

# end of file