#include "states.h"
#include "arduino.h"
#include "timer.h"
#include "button.h"
#include "motor.h"
#include "settings.h"
#include "epsonencoder.h"
#include "userinput.h"
#include "pins.h"

namespace
{
    bool twoPassTriggered = false;
}

State bootup(Timer& platenTimer, Button& backStopButton)
{

	static bool moveSwOff = false;

    if (backStopButton.isPressed() && !moveSwOff)
    {
		moveSwOff = true;
    }

	if (backStopButton.isPressed() && moveSwOff)
	{
		if (platenTimer.passedTime() > Settings::alignSpeed)
		{
			StepperMotor::takeStepForward();
			platenTimer.reset();
		}
	}

	if(!backStopButton.isPressed() && moveSwOff)
	{
		moveSwOff = false;
		StepperMotor::resetPosition();
		return State::MoveFront;
	}

    if(platenTimer.passedTime() > Settings::bootSpeed && !moveSwOff)
    {
        StepperMotor::takeStepReverse();
        platenTimer.reset();
    }

    return State::Bootup;
}

State moveBack(Timer& platenTimer, Button& backStopButton, UserInput userInput)
{
	setHigh(Pins::canAutoUsing);

    if(userInput == UserInput::OnePass)
        twoPassTriggered = false;
    else if(userInput == UserInput::TwoPass)
        twoPassTriggered = true;
    else if (userInput == UserInput::MoveFront)
      return State::MoveFront;

	if (isHigh(Pins::holdingPlate))
		return State::MoveBack;

    if (backStopButton.isPressed())
    {
        return State::StepOffLimitSwitch;
    }

    if(platenTimer.passedTime() > Settings::homeSpeed)
    {
        StepperMotor::takeStepReverse();
        platenTimer.reset();
    }

    return State::MoveBack;
}

State stepOffLimitSwitch(Timer& platenTimer, Button& backStopButton)
{
    //Slowly step carriage off back limit switch
    if(backStopButton.isPressed())
    {
        if(platenTimer.passedTime() > Settings::alignSpeed)
        {
            StepperMotor::takeStepForward();
            platenTimer.reset();
        }

        return State::StepOffLimitSwitch;
    }
	EpsonEncoder::reset();
	StepperMotor::resetPosition();
	//StepperMotor::disable();
	EpsonEncoder::enable();
	setLow(Pins::canAutoUsing);
    return State::IdleBack;
}

State idleBack(UserInput userInput)
{
    if(userInput == UserInput::OnePass)
        twoPassTriggered = false;
    else if(userInput == UserInput::TwoPass)
        twoPassTriggered = true;
	else if (userInput == UserInput::MoveFront)
	{
		EpsonEncoder::disable();
		return State::MoveFront;
	}

    //If printer is in sleep mode and we press home the encoder will move one position so we are checking for it to be above 1 before going into print state
    if(EpsonEncoder::hasMoved() && EpsonEncoder::position() > 1)
    {
        //sei();
        return State::Printing;
    }

    return State::IdleBack;
}

State printing(Timer& platenTimer, Button& backStopButton)
{
	setLow(Pins::canAutoUsing);

    static int targetPosition = 0;

    if(EpsonEncoder::hasMoved())
        targetPosition = EpsonEncoder::position() / Settings::stepperFactor;

    if(targetPosition != StepperMotor::position())
    {
        //EpsonEncoder has moved CW
        if (targetPosition > StepperMotor::position())
            StepperMotor::takeStepForward();

        //EpsonEncoder has movedd CCW
        if (targetPosition < StepperMotor::position()) 
            StepperMotor::takeStepReverse();
    }

    /* When the position on the page is between peMinEncoder and peMaxEncoder we trigger the epson
     * pe signal(paper signal). We trick the printer to belive it has paper and the actual printing
     * starts. If its already triggered we don't check.
     */
    //if(isHigh(Pins::peSignal) && (EpsonEncoder::position() > Settings::peMinEncoder && EpsonEncoder::position() < Settings::peMaxEncoder))
    //    setLow3V(Pins::peSignal);

    /* When the position on the page is at platenEdgeEncoderPosition it means we are at the end of the page and
     * we untrigger the pe signal (paper signal). The printer thinks it needs more paper
     */
    if (EpsonEncoder::isAtEdgeOfPlaten())
    {
		setHigh3V(Pins::peSignal);
		EpsonEncoder::disable();
		if (::twoPassTriggered)
        {
            twoPassTriggered = false;
            return State::MoveBack;
        }
        else
        {
            return State::MoveFront;
        }
    }

    return State::Printing;
}

State moveFront(Timer& platenTimer, UserInput userInput)
{
	setLow(Pins::canAutoUsing);

    if(userInput == UserInput::MoveBackOnePass)
    {
        return State::MoveBack;
    }
    else if(userInput == UserInput::MoveBackTwoPass)
    {
        ::twoPassTriggered = true;
        return State::MoveBack;
    }

    if(StepperMotor::position() > Settings::maxSteps)
    {
        StepperMotor::disable();
        return State::IdleFront;
    }

    if(platenTimer.passedTime() > Settings::ejectSpeed)
    {
        StepperMotor::takeStepForward();
        platenTimer.reset();
    }

    return State::MoveFront;
}

State idleFront(UserInput userInput)
{
    if(userInput == UserInput::MoveBackOnePass)
    {
        return State::MoveBack;
    }
    else if(userInput == UserInput::MoveBackTwoPass)
    {
        ::twoPassTriggered = true;
        return State::MoveBack;
    }
	setHigh(Pins::canAutoUsing);
    return State::IdleFront;
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
        case State::MoveBack:
            Serial.print("MoveBack");
            break;
        case State::StepOffLimitSwitch:
            Serial.print("StepOffLimitSwitch");
            break;
        case State::IdleBack:
            Serial.print("IdleBack");
            break;
        case State::Printing:
            Serial.print("Printing");
            break;
        case State::MoveFront:
            Serial.print("MoveFront");
            break;
        case State::IdleFront:
            Serial.print("IdleFront");
            break;
        case State::NOTSET:
            Serial.print("NOTSET");
            break;
        default:
            Serial.print("Default??");
            break;
    }
}
