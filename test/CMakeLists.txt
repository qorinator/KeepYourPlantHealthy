# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Tell CMake that we need the header files in these directories
include_directories("../include")
include_directories("../googletest/googletest/include")

find_package(Threads REQUIRED)

# Create a variable GTEST that holds the location of the gtest library
find_library(GTEST
	NAMES "gtest"
	PATHS ${PROJECT_SOURCE_DIR}/googletest/googletest/build
	NO_DEFAULT_PATH
)

####################################################################################
#
# Modify the following each time you add a new test executable
#
####################################################################################

# Create executables out of the associated .cpp files
add_executable(
	googletest_example
	googletest_example.cpp
)

# Tell Cmake to link theses executables with the gtest library
target_link_libraries(googletest_example ${GTEST} Threads::Threads)