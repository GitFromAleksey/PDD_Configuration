#include "userinput.h"
#include "button.h"
#include "timer.h"
#include "states.h"
#include "settings.h"
#include "pins.h"

extern boolean autoState;

UserInput checkUserInput(Button& upButton, Button& downButton, Button & autoButton)
{
    static bool blink = false;

	if(autoButton.isPressed() && !blink && isHigh(Pins::canAutoUsing))
	{ 

		autoState = !autoState;
		blink = true;
		if (autoState)
		{
			setHigh(Pins::autoOnLED);
			return UserInput::AutoMove;
		}

		setLow(Pins::autoOnLED);
		return UserInput::Manual;
	}
		
	if(autoButton.released() && blink)
		blink = false;

	if(upButton.isPressed())
        return UserInput::MoveUp;
    else if(downButton.isPressed())
        return UserInput::MoveDown;

    return UserInput::None;
}


