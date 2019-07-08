#ifndef STATES_H
#define STATES_H

/*  Our states and functions to execute one step around the loop for each state
 *
 *  The state enum is just names for our states to make it more clear in the code. (instead of numbers)
 *
 *  bootup()        - When the printer is booted we move the elevator slowly up until the limit switch is triggered;
 *  MoveDown()      - Moves the elevator to the down 
 *  stepOffLimit()  - When the elevator is in the up we move slowly of the limit switch to get the same starting point every time 
 *	StepOffSoftLimit - Lower limit of elevation
 *  autoMove()      - We are autoMove! 
 *  moveUp()		- Moves the elevator to the up 
 *  idleMove()	    - Elevator idle in the up
 */

class Button;
class Timer;
enum class UserInput;

enum class State
{
    Bootup,
    MoveDown,
    StepOffLimitSwitch,
	StepOffSoftLimit,
    AutoMove,
    MoveUp,
	IdleMove,
    NOTSET
};

State bootup(Timer& elevatorTimer, Button& upStopSwitch);
State moveUp(Timer& elevatorTimer, Button& upStopSwitch, UserInput userInput, unsigned pressedTime);
State stepOffLimitSwitch(Timer& elevatorTimer, Button& upStopSwitch);
State autoMove(Timer& elevatorTimer, Button& upStopSwitch, UserInput userInput);
State moveDown(Timer& elevatorTimer, UserInput userInput, unsigned pressedTime);
State idleMove(UserInput userInput);
unsigned int checkSpeed(unsigned pressedTime);

//Debug functions
void checkAndPrintStateChange(State currentState);
void printState(State state);

#endif
