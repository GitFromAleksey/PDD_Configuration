#ifndef USERINPUT_H
#define USERINPUT_H

class Button;
enum class State;

enum class UserInput {
    MoveDown,
    MoveUp,
    Manual,
    AutoMove,
    None
};

UserInput checkUserInput(Button& upButton, Button& downButton, Button& autoButton);

#endif
