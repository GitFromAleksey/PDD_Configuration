#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

// Set variables - These variables effect the operation of the printer base. Make changes to compensate for different build types.
namespace Settings {
    //true if input from desktop app should be enabled.
    const bool desktopAppEnabled = false;

    // Step delay. Lower is faster
    const unsigned fastSpeed = 200;
    const unsigned middleSpeed = 600;
    const unsigned slowSpeed = 800;
    // Speed of platen during boot up
    const unsigned bootSpeed = 250;

    const unsigned speedChangeDelay = 2;

    const uint8_t inButtonInterval = 8;
    const uint8_t outButtonInterval = 8;
	const uint8_t autoButtonInterval = 8;
    const uint8_t upStopButtonInterval = 7;

    //The folowing settings are related to what printer and transport system being used settings for P600 and 1430 is in the comments

    /* The total encoder position is divided by this number to calculate motor steps in relationship to encoder movement
     * Based on a stepper motor of 200 steps pr revolution and in our setup loop we set a a microstepping factor of 8 so 1600 steps per motor revolution.
     *
     * Value should be 17.0 for Epson P600 and 8.53 for Epson 1430 
     */

    const float stepperFactor = 17.0;
	/* Delay for correct timing signal to stepping motor driver
	*/

	const unsigned signalDriverDuration = 50;

    /* Maximum steps the motor takes to get from the back to the front. Controls where platen stops on eject. 
     * NOTE: This max steps is on a base with 26.5 inches of travel, 30 teeth pulley, and 800 steps per stepper motor revolution. */
	const unsigned minSteps = 0;
  const unsigned long maxSteps = 70000;

	const unsigned OutHigh3V = 165;  // using for PWM 3.3V
	const unsigned OutLow3V = 0;
}

#endif
