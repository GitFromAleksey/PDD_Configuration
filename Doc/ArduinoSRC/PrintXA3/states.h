#ifndef STATES_H
#define STATES_H

/*  Our states and functions to execute one step around the loop for each state
 *
 *  The state enum is just names for our states to make it more clear in the code. (instead of numbers)
 *
 *  bootup()        - When the printer is booted we move the platen slowly back until the limit switch is triggered;
 *  moveBack()      - Moves the printer to the back to make it ready for printing
 *  stepOffLimit()  - When the platen is in the back we move slowly of the limit switch to get the same starting point every time 
 *  idleBack()      - Platen idles in the back and printer is ready to receive a print job 
 *  printing()      - We are printing! The platen follows the movement of the printhead registered by the EpsonEncoder
 *  moveFront()     - Moves the platen to the front so we can load shirts or just idle
 *  idleFront()     - Platen idle in the front
 */

class Button;
class Timer;
enum class UserInput;

enum class State
{
    Bootup,
    MoveBack,
    StepOffLimitSwitch,
    IdleBack,
    Printing,
    MoveFront,
    IdleFront,
    NOTSET
};

State bootup(Timer& platenTimer, Button& backStopButton);
State moveBack(Timer& platenTimer, Button& backStopButton, UserInput userInput);
State stepOffLimitSwitch(Timer& platenTimer, Button& backStopButton);
State idleBack(UserInput userInput);
State printing(Timer& platenTimer, Button& backStopButton);
State moveFront(Timer& platenTimer, UserInput userInput);
State idleFront(UserInput userInput);

//Debug functions
void checkAndPrintStateChange(State currentState);
void printState(State state);

#endif
