#include "epsonencoder.h"
#include "settings.h"
#include "pins.h"
#include "states.h"

//#include <Encoder.h>

extern volatile boolean peState;
extern State platenState;

namespace
{
    //Encoder encoderWheel(Pins::encoderA, Pins::encoderB);
    long previousPosition;
	long position;
	uint8_t encState;

#define ENC_A   ((PIND & (1 << Pins::encoderA)) > 0)
#define ENC_B   ((PIND & (1 << Pins::encoderB)) > 0)

}

void EpsonEncoder::reset()
{
	::position = 0;
	::previousPosition = 0;

    //::encoderWheel.write(0);
    //::previousPosition = position();

}

bool EpsonEncoder::hasMoved()
{
    long newPosition = position();
    if(newPosition != ::previousPosition)
    {
        ::previousPosition = newPosition;
        return true;
    }
    return false;
}

long EpsonEncoder::position()
{
	return ::position;//::encoderWheel.read();
}

bool EpsonEncoder::isAtEdgeOfPlaten()
{
    return position() > Settings::platenEdgeEncoderPosition;
}

void EpsonEncoder::enable()
{
	attachInterrupt(0, onEncA, CHANGE);
	attachInterrupt(1, onEncB, CHANGE);
}

void EpsonEncoder::disable()
{
	detachInterrupt(0);
	detachInterrupt(1);
}

void EpsonEncoder::onEncA()
{
	update();
}

void EpsonEncoder::onEncB()
{
	update();
}

void EpsonEncoder::update() {
	//cli();

	uint8_t s = ::encState & 3;
	if (ENC_A) s |= 4;
	if (ENC_B) s |= 8;
	switch (s) {
	case 0: case 5: case 10: case 15:
		break;
	case 1: case 7: case 8: case 14:
		::position++; break;
	case 2: case 4: case 11: case 13:
		::position--; break;
	case 3: case 12:
		::position += 2; break;
	default:
		::position -= 2; break;
	}
	::encState = (s >> 2);

	//sei();

	//this section was inserted here to best performance
	if (platenState == State::Printing)
	{
		if (::position >= Settings::peEncoder && peState)
		{
			cli();
			setLow3V(Pins::peSignal);
			peState = false;
			sei();
		}
		if (::position < Settings::peEncoder && !peState)
		{
			cli();
			setHigh3V(Pins::peSignal);
			peState = true;
			sei();
		}
	}
}
