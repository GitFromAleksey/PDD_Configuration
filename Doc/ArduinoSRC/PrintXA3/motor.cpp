#include "motor.h"
#include "arduino.h"
#include "pins.h"
#include "settings.h"

namespace
{
    bool enabled = false;
    int position = 0;
};

void StepperMotor::takeStepForward()
{
    if(::enabled == false)
    {
		setLow(Pins::motorEnable);
        //digitalWrite(Pins::motorEnable, HIGH);
        enabled = true;
    }
    setLow(Pins::motorDirection);
    setHigh(Pins::motorStep);
	delayMicroseconds(Settings::signalDriverDuration);
    setLow(Pins::motorStep);
    ++::position;
}

void StepperMotor::takeStepReverse()
{
    if(!::enabled)
    {
		setLow(Pins::motorEnable);
		enabled = true;
    }
    setHigh(Pins::motorDirection);
    setHigh(Pins::motorStep);
	delayMicroseconds(Settings::signalDriverDuration);
    setLow(Pins::motorStep);
    --::position;
}

void StepperMotor::resetPosition()
{
    ::position = 0;
}

int StepperMotor::position()
{
    return ::position;
}

void StepperMotor::disable()
{
	setHigh(Pins::motorEnable);
	::enabled = false;
}
