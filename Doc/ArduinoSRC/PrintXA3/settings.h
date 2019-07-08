#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

// Set variables - These variables effect the operation of the printer base. Make changes to compensate for different build types.
namespace Settings {
    //true if input from desktop app should be enabled.
    const bool desktopAppEnabled = false;

    // Time delay for the ASF signal
    const unsigned asfInterval = 50000;

    // Step delay that controls platen eject speed. Lower is faster
    const unsigned ejectSpeed = 250;
    // Step delay that controls platen speed when homing at startup. Lower is faster
    const unsigned homeSpeed = 250;
    // Slows the step down when close to either end
    const unsigned slowSpeed = 750;
    // Speed of platen during boot up
    const unsigned bootSpeed = 250;
    // Step speed off of back limit switch
    const unsigned alignSpeed = 12500;

    const uint8_t inButtonInterval = 8;
    const uint8_t outButtonInterval = 8;
    const uint8_t backStopButtonInterval = 5;

    //The folowing settings are related to what printer and transport system being used settings for P600 and 1430 is in the comments

    /* The total encoder position is divided by this number to calculate motor steps in relationship to encoder movement
     * Based on a stepper motor of 200 steps pr revolution and in our setup loop we set a a microstepping factor of 8 so 1600 steps per motor revolution.
     *
     * Value should be 17.0 for Epson P600 and 8.53 for Epson 1430 
     */

    const float stepperFactor = 17.0;
	/* Delay for correct timing signal to stepping motor driver
	*/

	const unsigned signalDriverDuration = 10;

    /* Maximum steps the motor takes to get from the back to the front. Controls where platen stops on eject. 
     * NOTE: This max steps is on a base with 26.5 inches of travel, 30 teeth pulley, and 800 steps per stepper motor revolution. */
    const unsigned maxSteps = 10000;

    /* Encoder position from back until end of platen / print area. This triggers the eject after printing.
     *
     * P600 setting: 240000
     * 1430 setting: 130000 (Shared by randbyb123)
     */
    const unsigned long platenEdgeEncoderPosition = 240000;

    /* R3000 and P600 PE sensor Settings
     * Sets the range for the position of the Epson encoder and when to trigger the PE (Paper in) signal.
     *
     * NOTE: These default settings were tested on the Epson R3000 / P600. May be different on other models.
     */
    const unsigned peEncoder = 950;
    //const unsigned peMaxEncoder = 1050;

	const unsigned OutHigh3V = 165;  // using for PWM 3.3V
	const unsigned OutLow3V = 0;
}

#endif
