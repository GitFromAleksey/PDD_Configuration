#include "button.h"
#include "Bounce2.h"
#include "pins.h"

Button::Button(unsigned pin, unsigned interval, bool normalyOpen)
  : m_pin(pin)
  , m_interval(interval)
  , m_normalyOpen(normalyOpen)
{
}

void Button::setup(int type)
{
	pinMode(m_pin, type);
	m_bounce.attach(m_pin);
	m_bounce.interval(m_interval);
}

void Button::update(unsigned long deltaTime)
{
    m_released = false;
    m_bounce.update();
    if(m_normalyOpen)
        m_isPressed = m_bounce.read() == HIGH;
    else
        m_isPressed = !(m_bounce.read() == HIGH);

    if(!m_wasPressed && m_isPressed)
    {
        //start of press; reset time
        m_wasPressed = true;
        m_pressTime = 0;
    }
    else if(m_wasPressed && m_isPressed)
    {
        //Still pressed; add time
        m_pressTime += deltaTime;
    }
    else if(m_wasPressed && !m_isPressed)
    {
        //end of press
        m_released = true;
        m_wasPressed = false;
    }
}

bool Button::isPressed() const
{
    return m_isPressed;
}

bool Button::released() const
{
    return m_released;
}

unsigned long Button::pressTime() const
{
    return m_pressTime;
}
