#include "states.h"
#include "arduino.h"
#include "timer.h"
#include "button.h"
#include "motor.h"
#include "settings.h"
#include "userinput.h"
#include "pins.h"

namespace
{
}

extern boolean autoState;

State bootup(Timer& elevatorTimer, Button& upStopSwitch)
{
    if (upStopSwitch.isPressed())
    {
        return State::StepOffLimitSwitch;
    }

    if(elevatorTimer.passedTime() > Settings::bootSpeed)
    {
        StepperMotor::takeStepUp();
        elevatorTimer.reset();
    }

    return State::Bootup;
}

State moveUp(Timer& elevatorTimer, Button& upStopSwitch, UserInput userInput, unsigned pressedTime)
{
	if (userInput == UserInput::AutoMove || autoState)
		return State::AutoMove;
	else if (userInput == UserInput::MoveDown)
		return State::MoveDown;

	if (upStopSwitch.isPressed())
		return State::StepOffLimitSwitch;

	unsigned int speed = checkSpeed(pressedTime);

	if (userInput == UserInput::MoveUp)
	{
		if (StepperMotor::position() <= Settings::minSteps)
		{
			return State::IdleMove;
		}

		if (elevatorTimer.passedTime() > speed)
		{
			StepperMotor::takeStepUp();
			elevatorTimer.reset();
		}
	}


	return State::MoveUp;
}

State stepOffLimitSwitch(Timer& elevatorTimer, Button& upStopSwitch)
{
    //Slowly step carriage off back limit switch
    if(upStopSwitch.isPressed())
    {
        if(elevatorTimer.passedTime() > Settings::slowSpeed)
        {
            StepperMotor::takeStepDown();
            elevatorTimer.reset();
        }

        return State::StepOffLimitSwitch;
    }
	StepperMotor::resetPosition();
    return State::IdleMove;
}

State idleMove(UserInput userInput)
{
	if (userInput == UserInput::AutoMove)
	{
		return State::AutoMove;
	}
	else if (userInput == UserInput::MoveDown)
		return State::MoveDown;
	else if (userInput == UserInput::MoveUp)
		return State::MoveUp;

	return State::IdleMove;
}

State autoMove(Timer& elevatorTimer, Button& upStopSwitch, UserInput userInput)
{
	static boolean onlyUp = false;

	if ((!isHigh(Pins::canAutoUsing) && autoState)
		|| userInput == UserInput::Manual)
	{
		setLow(Pins::autoOnLED);
		autoState = false;
		setLow(Pins::holdPlattenSignal);
		onlyUp = false;
		return State::IdleMove;
	}

	if (!onlyUp)
	{
		setHigh(Pins::holdPlattenSignal);

		if (StepperMotor::position() < Settings::maxSteps && !isHigh(Pins::laserSensor))
		{
			if (elevatorTimer.passedTime() > Settings::middleSpeed)
			{
				StepperMotor::takeStepDown();
				elevatorTimer.reset();
			}
		}
		else
		{
			setLow(Pins::holdPlattenSignal);
			onlyUp = true;
		}
	}

	if (isHigh(Pins::laserSensor))
	{
		setHigh(Pins::holdPlattenSignal);
		if(StepperMotor::position() > 0 && !upStopSwitch.isPressed())
			if (elevatorTimer.passedTime() > Settings::slowSpeed)
			{
				StepperMotor::takeStepUp();
				elevatorTimer.reset();
			}
		return State::AutoMove;
	}

	setLow(Pins::holdPlattenSignal);
    return State::AutoMove;
}

State moveDown(Timer& elevatorTimer, UserInput userInput, unsigned pressedTime)
{
	if (userInput == UserInput::AutoMove || autoState)
		return State::AutoMove;
	else if (userInput == UserInput::MoveUp)
		return State::MoveUp;

	unsigned int speed = checkSpeed(pressedTime);

	if (userInput == UserInput::MoveDown)
	{
		if (StepperMotor::position() > Settings::maxSteps)
		{
			return State::IdleMove;
		}

		if (elevatorTimer.passedTime() > speed)
		{
			StepperMotor::takeStepDown();
			elevatorTimer.reset();
		}
	}


    return State::MoveDown;
}

unsigned int checkSpeed(unsigned pressedTime)
{
	unsigned int speed = Settings::slowSpeed;

	if (pressedTime >= Settings::speedChangeDelay && pressedTime < Settings::speedChangeDelay*2)
		speed = Settings::middleSpeed;
	if (pressedTime >= Settings::speedChangeDelay*2)
		speed = Settings::fastSpeed;
	return speed;
}

//Debug function
void checkAndPrintStateChange(State currentState)
{
    static State previousState = State::NOTSET;
    if(previousState != currentState)
    {
        Serial.print("State changed to: ");
        printState(currentState);
        Serial.print('\n');
    }
    previousState = currentState;
}

void printState(State state)
{
     switch (state)
    {
        case State::Bootup:
            Serial.print("Bootup");
            break;
        case State::MoveDown:
            Serial.print("MoveDown");
            break;
		case State::IdleMove:
			Serial.print("IdleMove");
			break;
        case State::StepOffLimitSwitch:
            Serial.print("StepOffLimitSwitch");
            break;
        case State::AutoMove:
            Serial.print("AutoMove");
            break;
        case State::MoveUp:
            Serial.print("MoveUp");
            break;
        case State::NOTSET:
            Serial.print("NOTSET");
            break;
        default:
            Serial.print("Default??");
            break;
    }
}
