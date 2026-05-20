cmake_minimum_required(VERSION 3.20.0)

project(tictactoe-lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/libs/libtttcore.a")
    message(STATUS "Using PREBUILT tttcore library from libs/")
    add_library(tttcore STATIC IMPORTED)
    set_target_properties(tttcore PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/libtttcore.a"
    )
    target_include_directories(tttcore INTERFACE src)
else()
    message(STATUS "Building tttcore from sources")
    set(core_src 
        src/core/event.cpp 
        src/core/game.cpp 
        src/core/state.cpp 
        src/core/field.cpp
    )
    add_library(tttcore STATIC ${core_src})
endif()

set(TTTCORE_LIB tttcore)

include_directories(src)

set(player_src 
    src/player/my_player.cpp 
    src/player/my_observer.cpp
)

add_library(tttplayer STATIC ${player_src})
target_link_libraries(tttplayer ${TTTCORE_LIB})

enable_testing()
add_subdirectory("tests")

add_executable(play_game main.cpp)
target_link_libraries(play_game tttplayer tttcore)