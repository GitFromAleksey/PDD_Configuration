#include "globals.h"



uint16_t ReadRegs[READ_REGS_SIZE];

uint16_t ReadWriteRegs[READ_WRITE_REGS_SIZE];

uint16_t GetReadRegValue(uint8_t regNum)
{
	return ReadRegs[regNum];
}

uint16_t GetReadWriteRegValue(uint8_t regNum)
{
	return ReadWriteRegs[regNum];
}

uint16_t SetReadWriteRegValue(uint8_t regNum, uint16_t data)
{
	ReadWriteRegs[regNum] = data;
	return 1;
}
