#ifndef MODBUS_H
#define MODBUS_H

#include "stdint.h"

#define READ_REGS_SIZE				10
#define READ_WRITE_REGS_SIZE	10

//uint16_t ReadRegs[READ_REGS_SIZE];
//uint16_t ReadWriteRegs[READ_WRITE_REGS_SIZE];

void ModbusInit(uint8_t (*transmitFunction)(uint8_t* Buf, uint16_t Len),
								int8_t (*receiveFunction)(uint8_t* Buf, uint32_t *Len));
void ModbusProcess(void);


#endif
