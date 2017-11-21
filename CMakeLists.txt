# Tell CMake which version of CMake is required
cmake_minimum_required(VERSION 3.7)

# Define our project name
project (KeepYourPlantHealhy)
#project (KeepYourPlantHealhy_tests)

# Tell CMake to go into other directories and read CMakeLists.txt file in those
# 	directories
# add_subdirectory(src)
add_subdirectory(test)