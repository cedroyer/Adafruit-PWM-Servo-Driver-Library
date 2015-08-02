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

#include "Adafruit_PWMServoDriver.h"

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
#if defined(__AVR__)
 #define WIRE Wire
#elif defined(CORE_TEENSY) // Teensy boards
 #define WIRE Wire
#else // Arduino Due
 #define WIRE Wire1
#endif

// Set to true to print some debug messages, or false to disable them.
#define ENABLE_DEBUG_OUTPUT true

void Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(std::uint8_t addr): _i2caddr(addr) {
}

void Adafruit_PWMServoDriver::begin(void) {
 WIRE.begin();
 reset();
}

void Adafruit_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);

  WIRE.beginTransmission(_i2caddr);
  WIRE.write(LED0_ON_L+4*num);
  WIRE.write(on);
  WIRE.write(on>>8);
  WIRE.write(off);
  WIRE.write(off>>8);
  WIRE.endTransmission();
}

uint8_t Adafruit_PWMServoDriver::read8(uint8_t addr) {
  WIRE.beginTransmission(_i2caddr);
  WIRE.write(addr);
  WIRE.endTransmission();

  WIRE.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return WIRE.read();
}

void Adafruit_PWMServoDriver::write8(uint8_t addr, uint8_t d) {
  WIRE.beginTransmission(_i2caddr);
  WIRE.write(addr);
  WIRE.write(d);
  WIRE.endTransmission();
}

void Adafruit_PWMServoDriver::pwmDelay(unsigned int millisec) {
	delay(millisec);
}

template <typename T>
void Adafruit_PWMServoDriver::printDebug(T const & value) {
	Serial.print(value);
}

template<typename T>
void Adafruit_PWMServoDriver::printDebugLn(T const & value) {
	Serial.println(value);
}
