#include "digitalInputs.h"


uint32_t inputs;
uint32_t (*getDigitalInputsState)(void);

void DI_Init(uint32_t (*_getDigitalInputsState)(void))
{
	inputs = 0;
	getDigitalInputsState = _getDigitalInputsState;
}

uint32_t DI_CheckInput(uint32_t input)
{
	if( (inputs & input) == input )
	{
		return (uint32_t)1;
	}
	else
	{
		return (uint32_t)0;
	}
}

void DI_Process(void)
{
	inputs = getDigitalInputsState();
}
