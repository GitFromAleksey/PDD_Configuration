#ifndef BUTTON_H
#define BUTTON_H

#include <Bounce2.h>

/*  Button class represent our button and keep track of presses and how long the button has been pressed
 *  It uses the Bounce library.
 *  
 *  Button()    - creates a button object.
 *  setup()     - run in arduinos setup function; attaches the pin to the bounce object and sets its interval
 *  update()    - updates the button state and tracking time of presses
 *  isPressed() - return true if button is pressed
 *  released()  - return true when the button is released. This is how a keyboard is programmed also; we
 *                don't want to keep changing state if the button is held down.
 *  pressTime() - returns the microseconds the button was pressed.
 */

class Button {
public:
    Button(unsigned pin, unsigned interval, bool normalyOpen = false);

    void setup(int type = 0x2);  //INPUT_PULLUP
    void update(unsigned long deltaTime);

    bool isPressed() const;
    bool released() const;
    unsigned long pressTime() const;

private:
    unsigned m_pin;
    unsigned m_interval;
    bool m_normalyOpen;
    bool m_isPressed;
    bool m_released;
    bool m_wasPressed;
    unsigned long m_pressTime;
    Bounce m_bounce;
};

#endif
