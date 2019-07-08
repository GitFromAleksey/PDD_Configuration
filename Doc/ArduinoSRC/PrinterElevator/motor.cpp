#include "motor.h"
#include "arduino.h"
#include "pins.h"
#include "settings.h"

namespace
{
    bool enabled = false;
    long position = 0;
};

void StepperMotor::takeStepUp()
{
    if(::enabled == false)
    {
		setLow(Pins::motorEnable);
        enabled = true;
    }
    setLow(Pins::motorDirection);
    setHigh(Pins::motorStep);
	delayMicroseconds(Settings::signalDriverDuration);
    setLow(Pins::motorStep);
    --::position;
}

void StepperMotor::takeStepDown()
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
    ++::position;
}

void StepperMotor::resetPosition()
{
    ::position = 0;
}

long StepperMotor::position()
{
    return ::position;
}

void StepperMotor::disable()
{
	setHigh(Pins::motorEnable);
	::enabled = false;
}
