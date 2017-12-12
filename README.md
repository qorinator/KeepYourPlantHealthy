# Keep Your Plant Healthy

This is the source code for Keep Your Plant Healthy Project.

The source code is divided into 3 parts : 

1. Arduino
2. Pi
3. Web

### Arduino

The main responsibility of the Arduino is to get the sensors' data, wrap the data and transmit the wrapped data via the USB.

#### Dependency

Install these Dependencies in your arduino library
```
https://github.com/maniacbug/StandardCplusplus.git
SI114x https://github.com/Seeed-Studio/Gardening_demo_Arduino.git
```
#### Hardware Set-Up (Groove Gardening Kit)

- Groove Baseshield V2
 - DHT11 - A0
 - Sunlight Sensor V1.0 - I2C
 - Moisture Sensor - A1
 - Waterflow Sensor - D5

### Pi

The main responsibility of the Raspbery Pi is to receive the data from Arduino, unwrap the data and store it into MySQL database.

#### Dependency

Install these Dependencies in your Pi
```
https://github.com/google/googletest.git
```

### Web

The main responsibiltiy of the Web is to get the data from MySQL database and post it in the website format.