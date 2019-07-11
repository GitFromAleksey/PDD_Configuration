#include "globals.h"
#include "stm32f1xx_hal.h"


uint16_t ReadRegs[READ_REGS_SIZE];

uint16_t ReadWriteRegs[READ_WRITE_REGS_SIZE];

uint16_t GetReadRegValue(uint8_t regNum)
{
	if(regNum >= READ_REGS_SIZE)
		return 0;
	return ReadRegs[regNum];
}

uint16_t GetReadWriteRegValue(uint8_t regNum)
{
	if(regNum >= READ_WRITE_REGS_SIZE)
		return 0;
	return ReadWriteRegs[regNum];
}



uint16_t SetReadWriteRegValue(uint8_t regNum, uint16_t data)
{
	ReadWriteRegs[regNum] = data;
	HAL_FLASH_Unlock();
	
	
	HAL_FLASH_Lock();
	// FLASH_PageErase(uint32_t PageAddress);
	// FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
	// HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
	// FLASH_WaitForLastOperation(uint32_t Timeout)
	return 1;
}
