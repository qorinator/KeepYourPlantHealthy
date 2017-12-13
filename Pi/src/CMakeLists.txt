# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


# Tell CMake that we need the header files in these directories
include_directories("../include")
include_directories("/usr/include/mysql")

# Create a variable that holds the location of the library
find_library(MYSQL_LIBRARY
	NAMES "mysqlclient"
	PATHS "/usr/include/mysql")

# Create executables out of the associated .cpp files
add_executable(UpdateDailyMeasurement
	UpdateDailyMeasurement.cpp
	ArduinoHandler.cpp
	SerialPort.cpp
	SPConfigure.cpp
	ProtocolUnwrapper.cpp
	SerialDataHandler.cpp
	Package.cpp
	KYPHSensors.cpp
	SQLQuery.cpp
	SQLInterface.cpp
	SQLInsert.cpp
	SQLObject.cpp
)

add_executable(StoreSensorMeasurement
 	StoreSensorMeasurement.cpp
 	SQLInterface.cpp
 	SQLUpdate.cpp
 	SQLObject.cpp
 	SQLQuery.cpp
 	KYPHSensors.cpp
 	Package.cpp
)

add_executable(ClearDailyMeasurement
	ClearDailyMeasurement.cpp
	SQLInterface.cpp
	SQLTruncate.cpp
	KYPHSensors.cpp
	Package.cpp
)

# Tell Cmake to link theses executables with the library
target_link_libraries(UpdateDailyMeasurement ${MYSQL_LIBRARY})
target_link_libraries(StoreSensorMeasurement ${MYSQL_LIBRARY})
target_link_libraries(ClearDailyMeasurement ${MYSQL_LIBRARY})
