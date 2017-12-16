#
#
#
set (target bzeditor)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(UI_HEADERS mainwindow.ui) 

add_executable(${target} 
	main.cc 
	mainwindow.cc 
	mainwindow.h 
	mainwindow.ui 
	rasterwindow.cpp 
	rasterwindow.h 
	drawingpanel.cpp
	drawingpanel.h
	${UI_HEADERS}
	bezierMk2.cc bezierMk2.h
	)
qt5_use_modules(${target} Widgets)
set_property(SOURCE ${UI_HEADERS} PROPERTY SKIP_AUTOMOC ON)

set_target_properties(${target} PROPERTIES FOLDER "apps")

# end of file
