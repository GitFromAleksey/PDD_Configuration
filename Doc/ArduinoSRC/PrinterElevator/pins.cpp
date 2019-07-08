#include "pins.h"
#include "CyberLib.h"
#include "settings.h"

void setupPin(uint8_t pin, uint8_t mode, uint8_t state)
{
    pinMode(pin, mode);
	if(mode == OUTPUT)
		digitalWrite(pin, state);
}


void setHigh(uint8_t pin)
{
	switch (pin)
	{
	case 0:D0_High; break;
	case 1:D1_High;break;
	case 2:D2_High;break;
	case 3:D3_High;break;
	case 4:D4_High;break;
	case 5:D5_High;break;
	case 6:D6_High;break;
	case 7:D7_High;break;
	case 8:D8_High; break;
	case 9:D9_High; break;
	case 10:D10_High; break;
	case 11:D11_High; break;
	case 12:D12_High; break;
	case 13:D13_High; break;
	case 14:D14_High; break;
	case 15:D15_High; break;
	case 16:D16_High; break;
	case 17:D17_High; break;
	case 18:D18_High; break;
	case 19:D19_High; break;

	default:break;
	}
    //digitalWrite(pin, HIGH);
}

void setLow(uint8_t pin)
{
	switch (pin)
	{
	case 0:D0_Low; break;
	case 1:D1_Low; break;
	case 2:D2_Low; break;
	case 3:D3_Low; break;
	case 4:D4_Low; break;
	case 5:D5_Low; break;
	case 6:D6_Low; break;
	case 7:D7_Low; break;
	case 8:D8_Low; break;
	case 9:D9_Low; break;
	case 10:D10_Low; break;
	case 11:D11_Low; break;
	case 12:D12_Low; break;
	case 13:D13_Low; break;
	case 14:D14_Low; break;
	case 15:D15_Low; break;
	case 16:D16_Low; break;
	case 17:D17_Low; break;
	case 18:D18_Low; break;
	case 19:D19_Low; break;

	default:break;
	}
    //digitalWrite(pin, LOW);
}

bool isHigh(uint8_t pin)
{
	switch (pin)
	{
	case 0:return D0_Read == HIGH; 
	case 1:return D1_Read == HIGH; 
	case 2:return D2_Read == HIGH; 
	case 3:return D3_Read == HIGH; 
	case 4:return D4_Read == HIGH; 
	case 5:return D5_Read == HIGH; 
	case 6:return D6_Read == HIGH; 
	case 7:return D7_Read == HIGH; 
	case 8:return D8_Read == HIGH; 
	case 9:return D9_Read == HIGH; 
	case 10:return D10_Read == HIGH;
	case 11:return D11_Read == HIGH;
	case 12:return D12_Read == HIGH;
	case 13:return D13_Read == HIGH;
	case 14:return D14_Read == HIGH;
	case 15:return D15_Read == HIGH;
	case 16:return D16_Read == HIGH;
	case 17:return D17_Read == HIGH;
	case 18:return D18_Read == HIGH;
	case 19:return D19_Read == HIGH;

	default:return false;
	}
    //return digitalRead(pin) == HIGH;
}

unsigned togglePin(uint8_t pin)
{
    if(isHigh(pin))
    {
        setLow(pin);
        return LOW;
    }
    else
    {
        setHigh(pin);
        return HIGH;
    }
}

