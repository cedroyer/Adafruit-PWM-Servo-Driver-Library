/*************************************************** 
  This is a library for our Adafruit 16-channel PWM & Servo driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <cstdint>

#ifndef _ADAFRUIT_PWMServoDriver_H
#define _ADAFRUIT_PWMServoDriver_H

#ifdef RPI_VERSION
#include <iostream>
#include <gnublin.h>
#endif

#define ENABLE_DEBUG_OUTPUT true

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


class Adafruit_PWMServoDriver {
 public:
#ifdef RPI_VERSION
  Adafruit_PWMServoDriver(const char* connector, std::uint8_t addr = 0x40);
#else
  Adafruit_PWMServoDriver(std::uint8_t addr = 0x40);
#endif
  void begin(void);
  void reset(void);
  void setPWMFreq(float freq);
  void setPWM(uint8_t num, uint16_t on, uint16_t off);
  void setPin(uint8_t num, uint16_t val, bool invert=false);

 private:
#ifdef RPI_VERSION
	gnublin_i2c i2c_;
#else
  uint8_t _i2caddr;
#endif

  uint8_t read8(uint8_t addr);
  void write8(uint8_t addr, uint8_t d);

	void pwmDelay(unsigned int millisec);

	template<typename T>
	void printDebug(T const &);

	template<typename T>
	void printDebugLn(T const &);
};

#ifdef RPI_VERSION
template<typename T>
void Adafruit_PWMServoDriver::printDebug(T const & val) {
	std::cout << val;
}
template<typename T>
void Adafruit_PWMServoDriver::printDebugLn(T const & val) {
	std::cout << val << '\n';
}
#elif ARDUINO_VERSION
#endif

#endif
