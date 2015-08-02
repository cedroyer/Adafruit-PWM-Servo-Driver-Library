test:
	g++ -std=c++11 -DRPI_VERSION -I gnublin-api/ -L gnublin-api/ -lgnublin Adafruit_PWMServoDriver_common.cpp Adafruit_PWMServoDriver_RPI.cpp test.cpp
