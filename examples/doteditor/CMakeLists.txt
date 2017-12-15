#
#
#

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(doteditor main.cc mainwindow.cc mainwindow.h)
qt5_use_modules(doteditor Widgets)

# end of file
