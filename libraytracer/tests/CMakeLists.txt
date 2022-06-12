cmake_minimum_required(VERSION 3.22)

project(libraytracer_tests)

set(CMAKE_CXX_STANDARD 20)

# google test sources
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../libraytracer)

# test executable to run
# test_*.cpp are source files with tests
add_executable(libraytracer_tests_run test_tuples.cpp ../libraytracer/tuples.cpp ../libraytracer/colours.cpp test_colours.cpp ../libraytracer/canvas.cpp test_canvas.cpp ../libraytracer/matrix_2d.cpp test_matrix_2d.cpp)
target_link_libraries(libraytracer_tests_run gtest gtest_main)






