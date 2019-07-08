#include "timer.h"
#include "arduino.h"

unsigned long Time::getDeltaTime()
{
    static unsigned long previous = 0;

    unsigned long current = micros();
    unsigned long deltaTime = current - previous;
    previous = current;
    return deltaTime;
}

unsigned long Time::secondsToMicros(float seconds)
{
    return seconds * 1000000;
}

unsigned Time::microsToSeconds(unsigned long microseconds)
{
	return microseconds/1000000;
}

Timer::Timer()
    : m_passedTime(0)
{

}

void Timer::reset()
{
    m_passedTime = 0;
}

void Timer::update(unsigned long deltaTime)
{
    m_passedTime += deltaTime;
}

unsigned long Timer::passedTime()
{
    return m_passedTime;
}
