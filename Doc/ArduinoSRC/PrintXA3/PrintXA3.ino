/* DTG Arduino All in One V1 board for Epson 1430, R3000 and P600 Models
* http://www.printx.spb.ru/
*
*
* 30.04.2019 - First reduction.
*
*/

#include "settings.h"
#include "Button.h"
#include "pins.h"
#include "timer.h"
#include "userinput.h"
#include "states.h"


/* The last boolean of these instantations are if the buttons are normaly open or not.
 * If you don't use the standard buttons that isn't normally open buttons change these values to false.
 */
Button inButton(Pins::inBtn, Settings::inButtonInterval, false);
Button outButton(Pins::outBtn, Settings::outButtonInterval, false);
Button backStopButton(Pins::backStop, Settings::backStopButtonInterval, true);

State platenState;
volatile boolean peState; //signal PE is inversed

void setup() 
{
    if (Settings::desktopAppEnabled)
        Serial.begin(9600);

	platenState = State::Bootup;
	peState = true;
    //Motor pin setup
    setupPin(Pins::motorEnable, OUTPUT, HIGH);
    setupPin(Pins::motorStep, OUTPUT, LOW);
    setupPin(Pins::motorDirection, OUTPUT, LOW);
 
    setupPin(Pins::peSignal, OUTPUT);
    setupPin(Pins::powerLED, OUTPUT, HIGH);
    setupPin(Pins::asfSignal, OUTPUT);

	setupPin(Pins::canAutoUsing, OUTPUT, LOW);
	setupPin(Pins::holdingPlate, INPUT);

	setHigh3V(Pins::peSignal);
	setLow3V(Pins::asfSignal);

    //Buttons setup
    inButton.setup();
    outButton.setup();
    backStopButton.setup();

}

void loop()
{
    static Timer platenTimer;
    static Timer asfTimer;
	static boolean ASF = false;

	label:

    unsigned deltaTime = Time::getDeltaTime();

    platenTimer.update(deltaTime);
    asfTimer.update(deltaTime);

    inButton.update(deltaTime);
    outButton.update(deltaTime);
    backStopButton.update(deltaTime);

    UserInput userInput = checkUserInput(inButton, outButton);
 
    if(asfTimer.passedTime() > Settings::asfInterval)
    {
		if (ASF)
		{
			setLow3V(Pins::asfSignal);
			ASF = false;
		}
		else
		{
			setHigh3V(Pins::asfSignal);
			ASF = true;
		}
         //togglePin(Pins::asfSignal);
         asfTimer.reset();
    }

    checkAndPrintStateChange(platenState);
    switch (platenState)
    {
        case State::Bootup:
            platenState = bootup(platenTimer, backStopButton);
            break;
        case State::MoveBack:
            platenState = moveBack(platenTimer, backStopButton, userInput);
            break;
        case State::StepOffLimitSwitch:
            platenState = stepOffLimitSwitch(platenTimer, backStopButton);
            break;
        case State::IdleBack:
            platenState = idleBack(userInput);
            break;
        case State::Printing:
            platenState = printing(platenTimer, backStopButton);
            break;
        case State::MoveFront:
            platenState = moveFront(platenTimer, userInput);
            break;
        case State::IdleFront:
            platenState = idleFront(userInput);
            break;
        default:
            break;
    }

	goto label;
}
