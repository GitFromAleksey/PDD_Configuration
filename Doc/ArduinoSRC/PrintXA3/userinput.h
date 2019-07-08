#ifndef USERINPUT_H
#define USERINPUT_H

class Button;
enum class State;

enum class UserInput {
    MoveBackOnePass,
    MoveBackTwoPass,
    MoveFront,
    OnePass,
    TwoPass,
    None
};

UserInput checkUserInput(Button& inButton, Button& outButton);

#endif
