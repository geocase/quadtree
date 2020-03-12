cmake_minimum_required(VERSION 3.10)

project(qtree)
include_directories(inc)
find_package(SDL2 REQUIRED)
file(GLOB SOURCES src/*.cc)


add_executable(qtree ${SOURCES})

target_compile_options(qtree PRIVATE -std=c++17 -g -O2 -Wpedantic -Wall)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})


