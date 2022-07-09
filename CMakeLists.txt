cmake_minimum_required(VERSION 3.22)

project(raytracer_challenge)

set(CMAKE_CXX_STANDARD 20)

include_directories(libraytracer)

add_subdirectory(libraytracer/tests)

add_executable(raytracer raytracer/raytracer/main.cpp libraytracer/libraytracer/tuples.cpp libraytracer/libraytracer/colours.cpp libraytracer/libraytracer/canvas.cpp libraytracer/libraytracer/matrix_2d.cpp libraytracer/libraytracer/rays.cpp libraytracer/libraytracer/rays.h libraytracer/libraytracer/shapes.cpp libraytracer/libraytracer/shapes.h libraytracer/libraytracer/intersection.cpp libraytracer/libraytracer/intersection.h libraytracer/libraytracer/lighting.cpp libraytracer/libraytracer/lighting.h libraytracer/libraytracer/materials.cpp libraytracer/libraytracer/materials.h libraytracer/libraytracer/world.cpp libraytracer/libraytracer/world.h)




