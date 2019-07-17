#ifndef _DIGITALOUTPUTS_H
#define _DIGITALOUTPUTS_H

#include "stdint.h"

void DO_Init( void (*_setReset_PE_Signal)(uint32_t set_reset),
							void (*_asf_SignalOnOff)(uint32_t period, uint32_t enable) );

void DO_PE_Signal(uint32_t set_reset);
void DO_ASF_Signal(uint32_t period, uint32_t enable);

#endif /*_DIGITALOUTPUTS_H */
