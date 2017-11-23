<<<<<<< HEAD:src/CMakeLists.txt
# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# Tell CMake that we need the header files in these directories
include_directories("../include")

# Create executables out of the associated .cpp files
add_executable(KeepYourPlantHealhyExecutable
	KeepYourPlantHealthy.cpp
	ConfigureSerialPort.cpp
	SerialPort.cpp
	MessageDecoder.cpp
)

=======
# Set up the compiler flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# Tell CMake that we need the header files in these directories
include_directories("../include")

# Create executables out of the associated .cpp files
add_executable(KeepYourPlantHealhyExecutable
	KeepYourPlantHealthy.cpp
	ConfigureSerialPort.cpp
	SerialPort.cpp
	SerialPortMessageDecoder.cpp
)

>>>>>>> 1ba89d320f2e8927a945ad56c129ce00a27a3754:Pi/src/CMakeLists.txt
