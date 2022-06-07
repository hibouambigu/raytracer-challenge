cmake_minimum_required(VERSION 3.22)

project(raytracer_challenge)

set(CMAKE_CXX_STANDARD 20)

include_directories(libraytracer)

add_subdirectory(libraytracer/tests)

add_executable(raytracer raytracer/raytracer/main.cpp libraytracer/libraytracer/tuples.cpp)




