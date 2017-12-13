# Tell CMake which version of CMake is required
cmake_minimum_required(VERSION 3.7)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


# Define our project name
project (KeepYourPlantHealhy)
project (KeepYourPlantHealhy_tests)

# Tell CMake to go into other directories and read CMakeLists.txt file in those
# 	directories
add_subdirectory(src)
add_subdirectory(test)