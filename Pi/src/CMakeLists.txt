# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# Tell CMake that we need the header files in these directories
include_directories("../include")
include_directories("/usr/include/mysql")

# Create a variable that holds the location of the library
find_library(MYSQL_LIBRARY
	NAMES "mysqlclient"
	PATHS "/usr/include/mysql")

# Create executables out of the associated .cpp files
add_executable(DailyMeasurement
	DailyMeasurement.cpp	
	SerialPort.cpp
	SPConfigure.cpp
	ProtocolUnwrapper.cpp
	Package.cpp
	SerialDataHandler.cpp
	KYPHSensors.cpp
	SQLInterface.cpp
)

add_executable(WeeklyMeasurement
	WeeklyMeasurement.cpp
	SQLInterface.cpp
	KYPHSensors.cpp
	Package.cpp
)

add_executable(ClearDailyMeasurement
	ClearDailyMeasurement.cpp
	SQLInterface.cpp
	KYPHSensors.cpp
	Package.cpp
)

# Tell Cmake to link theses executables with the library
target_link_libraries(DailyMeasurement ${MYSQL_LIBRARY})
target_link_libraries(WeeklyMeasurement ${MYSQL_LIBRARY})
target_link_libraries(ClearDailyMeasurement ${MYSQL_LIBRARY})
