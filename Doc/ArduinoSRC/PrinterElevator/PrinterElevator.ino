/* Printer elevation programm with auto mode
* http://www.printx.spb.ru/
*
*
* 02.05.2019 - First reduction.
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
Button upButton(Pins::upBtn, Settings::inButtonInterval, false);
Button downButton(Pins::downBtn, Settings::outButtonInterval, false);
Button autoButton(Pins::autoBtn, Settings::autoButtonInterval, false);
Button upStopSwitch(Pins::upStop, Settings::upStopButtonInterval, true);


State elevatorState;
boolean autoState; 

void setup() 
{
    if (Settings::desktopAppEnabled)
        Serial.begin(9600);

	elevatorState = State::Bootup;
	autoState = false;
    //Motor pin setup
    setupPin(Pins::motorEnable, OUTPUT, LOW);
    setupPin(Pins::motorStep, OUTPUT, LOW);
    setupPin(Pins::motorDirection, OUTPUT, LOW);
 
    setupPin(Pins::holdPlattenSignal, OUTPUT, LOW);
    setupPin(Pins::autoOnLED, OUTPUT, LOW);
	setupPin(Pins::laserSensor, INPUT);
	setupPin(Pins::canAutoUsing, INPUT);


    //Buttons setup
    upButton.setup();
    downButton.setup();
	autoButton.setup();
    upStopSwitch.setup(INPUT);

}

void loop()
{
    static Timer elevatorTimer;

	label:

    unsigned deltaTime = Time::getDeltaTime();
	unsigned pressSeconds = 0;

    elevatorTimer.update(deltaTime);

    upButton.update(deltaTime);
    downButton.update(deltaTime);
	autoButton.update(deltaTime);
    upStopSwitch.update(deltaTime);

    UserInput userInput = checkUserInput(upButton, downButton, autoButton);

    checkAndPrintStateChange(elevatorState);
    switch (elevatorState)
    {
        case State::Bootup:
            elevatorState = bootup(elevatorTimer, upStopSwitch);
            break;
		case State::IdleMove:
			elevatorState = idleMove(userInput);
			break;
        case State::MoveUp:
			pressSeconds = Time::microsToSeconds(upButton.pressTime());
            elevatorState = moveUp(elevatorTimer, upStopSwitch, userInput, pressSeconds);
            break;
        case State::StepOffLimitSwitch:
            elevatorState = stepOffLimitSwitch(elevatorTimer, upStopSwitch);
            break;
        case State::AutoMove:
            elevatorState = autoMove(elevatorTimer, upStopSwitch, userInput);
            break;
        case State::MoveDown:
			pressSeconds = Time::microsToSeconds(downButton.pressTime());
            elevatorState = moveDown(elevatorTimer, userInput, pressSeconds);
            break;
        default:
            break;
    }

	goto label;
}
