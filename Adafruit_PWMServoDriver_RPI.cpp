#define BOARD RASPBERRY_PI
#include "Adafruit_PWMServoDriver.h"
#include <unistd.h> 
 
Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(const char* connector, uint8_t addr) : i2c_(connector, addr)
{}

void Adafruit_PWMServoDriver::begin() {
	reset();
}

void Adafruit_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  //Serial.print("Setting PWM "); Serial.print(num); Serial.print(": "); Serial.print(on); Serial.print("->"); Serial.println(off);
	uint8_t buffer[5] = {static_cast<uint8_t>(LED0_ON_L+4*num),
	 static_cast<uint8_t>(on),
	 static_cast<uint8_t>(on >> 8),
	 static_cast<uint8_t>(off),
	 static_cast<uint8_t>(off >> 8)};
  i2c_.send(buffer, 5);
}

uint8_t Adafruit_PWMServoDriver::read8(uint8_t addr) {
	uint8_t ret;
	i2c_.receive(addr, &ret, 1);
  return ret;
}

void Adafruit_PWMServoDriver::write8(uint8_t addr, uint8_t d) {
  i2c_.send(addr, &d, 1);
}

void Adafruit_PWMServoDriver::pwmDelay(unsigned int millisec) {
	usleep(millisec);
}

/*
int mainExample()
{
	gnublin_i2c i2c;

	i2c.setAddress(0x42); // set the address of the slave you want to read/write

	char buffer[8];
	char RxBuf[8];

	buffer[0]=0x22;

	i2c.send(buffer,5);
	i2c.send(0x12, buffer, 2);   //send 2 bytes from buffer to register-address 0x12

	i2c.receive(RxBuf, 3);       // read 3 bytes and store them in RxBuf
	i2c.receive(0x23, RxBuf, 3);  // read from  tegister-address 0x23 3 bytes and store them in RxBuf

}*/
