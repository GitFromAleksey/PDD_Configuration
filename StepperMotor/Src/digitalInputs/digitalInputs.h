#ifndef _DIGITALINPUTS_H
#define _DIGITALINPUTS_H

#include "stdint.h"

#define FLAT_BACK_LIMIT					(1<<0)
#define PRINTER_HIGHT_UP_LIMIT	(1<<1)
#define LASER_SENSOR						(1<<2)

void DI_Init(uint32_t (*_getDigitalInputsState)(void));
uint32_t DI_CheckInput(uint32_t input);
void DI_Process(void);

#endif /*_DIGITALINPUTS_H */
