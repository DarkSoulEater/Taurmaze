cmake_minimum_required(VERSION 3.17)
project(Taurmaze)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/game/maze.h
        src/core/Core.cpp
        src/core/Core.h
        src/game/Grid.cpp
        src/game/Grid.h
        src/util/input.cpp
        src/util/input.h
        src/util/path.h
        src/core/Object.cpp
        src/core/Object.h
        src/game/maze.cpp
        src/util/asset.cpp
        src/util/asset.h
        src/UI/Button.cpp
        src/UI/Button.h
        src/game/settings.cpp
        src/game/settings.h src/core/Scene.cpp src/core/Scene.h src/game/Player.cpp src/game/Player.h src/game/Buff.cpp src/game/Buff.h src/UI/Panel.cpp src/UI/Panel.h)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)