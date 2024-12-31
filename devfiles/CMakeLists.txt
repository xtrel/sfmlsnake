cmake_minimum_required(VERSION 3.28.3)
project(Snake VERSION 0.0.0.0)

add_executable(${CMAKE_PROJECT_NAME} 
	source/gameloop.cpp
	source/gameloopgetplayername.cpp
	source/leaderboardmenu.cpp
	source/mainheader.h
	source/mainmenu.cpp
	source/mainmenufunctions.cpp
	source/mainmenuheader.h
	source/settingsmenu.cpp
	source/snake.cpp
	source/txtfiles.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TinyFileDialogs

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/tinyfiledialogs.c)

# SFML

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/include)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/lib/libsfml-graphics.so.2.6.2)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/lib/libsfml-window.so.2.6.2)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML/lib/libsfml-system.so.2.6.2)