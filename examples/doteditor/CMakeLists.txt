#
#
#

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(UI_HEADERS mainwindow.ui) 

add_executable(doteditor 
	main.cc 
	mainwindow.cc 
	mainwindow.h 
	mainwindow.ui 
	rasterwindow.cpp 
	rasterwindow.h 
	drawingpanel.cpp
	drawingpanel.h
	${UI_HEADERS}
	)
qt5_use_modules(doteditor Widgets)
set_property(SOURCE ${UI_HEADERS} PROPERTY SKIP_AUTOMOC ON)

set_target_properties(doteditor PROPERTIES FOLDER "examples")

# end of file
