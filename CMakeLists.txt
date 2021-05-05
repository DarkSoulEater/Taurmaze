cmake_minimum_required(VERSION 3.17)
project(Taurmaze)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taurmaze main.cpp Maze.h Core.cpp Core.h Grid.cpp Grid.h input.cpp input.h path.h Object.cpp Object.h Buffer.cpp Buffer.h Clickable.cpp Clickable.h Drawable.cpp Drawable.h Maze.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Taurmaze sfml-graphics sfml-audio)