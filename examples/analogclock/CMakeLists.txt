#
#
#
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(analogclock main.cpp rasterwindow.cpp rasterwindow.h)
qt5_use_modules(analogclock Widgets)

set_target_properties(analogclock PROPERTIES FOLDER "examples")

# end of file
