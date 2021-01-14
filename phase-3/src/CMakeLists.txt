cmake_minimum_required(VERSION 2.6)

project ("demo_sdl2" LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall -lm")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
# find_package(SDL2_gfx REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(gyges.out main.c window.c board.c game.c)
target_link_libraries(gyges.out
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_TTF_LIBRARY} m)