# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# Tell CMake that we need the header files in these directories
include_directories("../include")

# Create executables out of the associated .cpp files
add_executable(KeepYourPlantHealhyExecutable
	KeepYourPlantHealthy.cpp	
	SerialPort.cpp
	SPConfigure.cpp
	ProtocolUnwrapper.cpp
	Package.cpp
	SerialDataHandler.cpp
	KYPHSensors.cpp
	MessageDecoder.cpp
)

