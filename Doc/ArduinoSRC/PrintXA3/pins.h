#ifndef PINS_H
#define PINS_H

#include <arduino.h>
#include <stdint.h>

void setupPin(uint8_t pin, uint8_t mode, uint8_t state);
void setupPin(uint8_t pin, uint8_t mode);
void setHigh(uint8_t pin);
void setLow(uint8_t pin);
void setHigh3V(uint8_t pin);
void setLow3V(uint8_t pin);
bool isHigh(uint8_t pin);
unsigned togglePin(uint8_t pin);


namespace Pins
{
    // Assign Arduino Pin Numbers. Use these numbers to wire your arduino correctly. All numbers are to Digital Pins on the Arduino Uno.

    // Encoder input from epson printer. Arduino Uno uses pins 2 and 3 for interrupts
    const uint8_t encoderA = 3;
    const uint8_t encoderB = 2;

    // Momentary push button to send the Platen to the Back / Home position - Other switch wire goes to Arduino Ground
    const uint8_t inBtn = 4;
    // Momentary push button to eject the platen to the front position  - Other switch wire goes to Arduino Ground
    const uint8_t outBtn = 5;
    // Automatic 2 pass Rocker style switch - Other switch wire goes to Arduino Ground
    const uint8_t passBtn = 6; 

	//Setup for TB6600 Stepper Driver
	const uint8_t motorEnable = 7;
	// Wire to motor driver direction pin
	const uint8_t motorDirection = 8;
	// Wire to motor driver Step / Pulse pin
	const uint8_t motorStep = 9;

    // Write HIGH or LOW - Hardware limits voltage output to 3v to protect Epson
    const uint8_t peSignal = 10;
    // Sends HIGH or LOW to Epson to similate ASF sensor. Hardware limits voltage to 3v to protect Epson
    const uint8_t asfSignal = 11;

    const uint8_t powerLED = 19;

	// Back or Home position. This is the rear limit switch used to stop the platen at the back of your machine.
	const uint8_t backStop = 12;

	//permission signal to printer elevator to using Auto mode
	const uint8_t canAutoUsing = 13;
	//holding plate signal from printer elevator
	const uint8_t holdingPlate = 14;

}

#endif
