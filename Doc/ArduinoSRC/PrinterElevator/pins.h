#ifndef PINS_H
#define PINS_H

#include <arduino.h>
#include <stdint.h>

void setupPin(uint8_t pin, uint8_t mode, uint8_t state = LOW);
void setHigh(uint8_t pin);
void setLow(uint8_t pin);
bool isHigh(uint8_t pin);
unsigned togglePin(uint8_t pin);


namespace Pins
{
    // Assign Arduino Pin Numbers. Use these numbers to wire your arduino correctly. All numbers are to Digital Pins on the Arduino Uno.


    // Momentary push button to go elevator up  - Other switch wire goes to Arduino Ground
    const uint8_t upBtn = 4;
    // Momentary push button to go elevator down  - Other switch wire goes to Arduino Ground
    const uint8_t downBtn = 5;
    // Automatic maintenance of height switch - Other switch wire goes to Arduino Ground
    const uint8_t autoBtn = 6; 

	//Setup for TB6600 Stepper Driver
	const uint8_t motorEnable = 7;
	// Wire to motor driver direction pin
	const uint8_t motorDirection = 8;
	// Wire to motor driver Step / Pulse pin
	const uint8_t motorStep = 9;

    // Write HIGH or LOW - output signal for holding platten feed to adjust altitude
    const uint8_t holdPlattenSignal = 10;

	// Home position. This is the up limit switch used to stop the elevator at the up of machine.
	const uint8_t upStop = 12;

	const uint8_t autoOnLED = 13;

	// laser sensor input
	const uint8_t laserSensor = 14;
	//permission signal from main CPU to using Auto mode
	const uint8_t canAutoUsing = 15;


}

#endif
