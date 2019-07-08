#include "userinput.h"
#include "button.h"
#include "timer.h"
#include "states.h"
#include "settings.h"
#include "pins.h"

UserInput checkUserInput(Button& inButton, Button& outButton)
{
    static bool previousPassBtn = isHigh(Pins::passBtn);
    if(previousPassBtn != isHigh(Pins::passBtn))
    {
        previousPassBtn = isHigh(Pins::passBtn);
        if(isHigh(Pins::passBtn))
            return UserInput::TwoPass;
        return UserInput::OnePass;
    }

    if(inButton.isPressed() && !isHigh(Pins::passBtn))
        return UserInput::MoveBackOnePass;
    else if(inButton.isPressed() && isHigh(Pins::passBtn))
        return UserInput::MoveBackTwoPass;
    else if(outButton.isPressed())
        return UserInput::MoveFront;

    if (Settings::desktopAppEnabled && Serial.available() > 0)
    {
        int desktopAppMessage = Serial.read();

        if(desktopAppMessage == 0)
            return UserInput::MoveBackOnePass;
        else if(desktopAppMessage == 1)
            return UserInput::MoveBackTwoPass;
        else if(desktopAppMessage == 2)
            return UserInput::MoveFront;
    }


    return UserInput::None;
}
