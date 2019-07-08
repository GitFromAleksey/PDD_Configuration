#ifndef TIME_H
#define TIME_H

/*  Functions to keep track of time and a stop watch timer abstraction
 *
 * getDeltaTime()       - returns the time since last time it was called in micro seconds
 * secondsToMicros()    - calculates the seconds to microseconds
 *
 * resetTimer()         - resets the timer to 0
 * updateTimer()        - updates the passed time by adding the deltaTime to the stored time
 * passedTime()         - returns the passed time since resetTimer was called
 */

namespace Time
{
    unsigned long getDeltaTime();
    unsigned long secondsToMicros(float seconds);
	unsigned microsToSeconds(unsigned long microseconds);
}

class Timer
{
public:
    Timer();

    void reset();
    void update(unsigned long deltaTime);
    unsigned long passedTime();
private:
    unsigned long m_passedTime;
};

#endif
