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

find_library(SFML_LIB libsfml-dev)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "${SFML_LIB}")
