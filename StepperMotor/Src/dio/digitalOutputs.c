#include "digitalOutputs.h"

void (*setReset_PE_Signal)(uint32_t set_reset);
void (*asf_SignalOnOff)(uint32_t period, uint32_t enable);

void DO_Init( void (*_setReset_PE_Signal)(uint32_t set_reset),
							void (*_asf_SignalOnOff)(uint32_t period, uint32_t enable) )
{
	setReset_PE_Signal = _setReset_PE_Signal;
	asf_SignalOnOff = _asf_SignalOnOff;
}

void DO_PE_Signal(uint32_t set_reset)
{
	setReset_PE_Signal(set_reset);
}

void DO_ASF_Signal(uint32_t period, uint32_t enable)
{
	asf_SignalOnOff(period, enable);
}
