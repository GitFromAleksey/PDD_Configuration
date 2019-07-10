#ifndef MODBUS_H
#define MODBUS_H

#include "stdint.h"


void ModbusInit(uint8_t (*transmitFunction)(uint8_t* Buf, uint16_t Len),
								int8_t (*receiveFunction)(uint8_t* Buf, uint32_t *Len));
void ModbusProcess(void);


#endif
