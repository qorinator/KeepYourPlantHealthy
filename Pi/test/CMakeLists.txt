# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
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
	SerialDataHandler_test
	SerialDataHandler_test.cpp
	../src/SerialDataHandler.cpp
)
target_link_libraries(SerialDataHandler_test ${GTEST} Threads::Threads)

add_executable(
	ProtocolUnwrapper_test
	ProtocolUnwrapper_test.cpp
	../src/ProtocolUnwrapper.cpp
	../src/SerialDataHandler.cpp
	../src/Package.cpp
)
target_link_libraries(ProtocolUnwrapper_test ${GTEST} Threads::Threads)

add_executable(
	SQLQuery_test
	SQLQuery_test.cpp
	../src/SQLQuery.cpp	
	../src/SQLObject.cpp
	../src/Package.cpp
	../src/KYPHSensors.cpp
)
target_link_libraries(SQLQuery_test ${GTEST} Threads::Threads)

add_executable(
	KYPHSensors_test
	KYPHSensors_test.cpp
	../src/Package.cpp
	../src/KYPHSensors.cpp
)
target_link_libraries(KYPHSensors_test ${GTEST} Threads::Threads)