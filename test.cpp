#include "Adafruit_PWMServoDriver.h"
#include <unistd.h> 
#include <cstdlib>
#include <iostream>

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(Adafruit_PWMServoDriver& pwm, uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  //Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  //Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  //Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

int main(int argc, char ** argv) {
	if(argc == 3) {
		Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver("/dev/i2c-1");
		pwm.begin();
		pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
		int servo = strtol(argv[1],NULL,10);
		int permille = strtol(argv[2],NULL,10);
		std::cout << "servo: " << servo << " permille: " << permille << std::endl;
		pwm.setPWM(servo, 0, (permille * (SERVOMAX - SERVOMIN)) / 1000 + SERVOMIN);
		usleep(1000000);
		pwm.setPWM(servo, 0, 0);
	}
	// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
	// pwm.begin();
	// pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
	//for (size_t i = 0; i < 1; ++i ){
  // for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
  //   //pwm.setPWM(0, 0, pulselen);
  //   pwm.setPWM(1, 0, pulselen);
	// 	usleep(10000);
  // }
	
	usleep(15000);
}
