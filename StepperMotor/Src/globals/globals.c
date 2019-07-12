#include "globals.h"
#include "stm32f1xx_hal.h"

#define ADDR_FLASH_PAGE_63		((uint32_t)0x0800FC00) // last memory page

uint16_t ReadRegs[READ_REGS_SIZE];

uint16_t ReadWriteRegs[READ_WRITE_REGS_SIZE];

void LoadAllDataFromFlash(void);

// ------------
uint32_t ReadOneRegFromFlash(uint32_t regAddr)
{
	return (*(__IO uint32_t*)( ADDR_FLASH_PAGE_63 + (regAddr*4)) );
}

// ------------
void WriteOneRegToFlash(uint32_t regAddr, uint16_t data)
{
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ADDR_FLASH_PAGE_63+(regAddr*4), (uint32_t)data);
	HAL_FLASH_Lock();
}

// ------------
uint16_t GetReadRegValue(uint8_t regNum)
{
	if(regNum >= READ_REGS_SIZE)
		return 0;
	return ReadRegs[regNum];
}

void GlobalsInit(void)
{
	uint32_t i = 0;
	for(i = 0; i < READ_REGS_SIZE; ++i)
	{
		ReadRegs[i] = 0;
	}
	for(i = 0; i < READ_WRITE_REGS_SIZE; ++i)
	{
		if(ReadOneRegFromFlash(i) == 0xFFFFFFFF)
		{
			WriteOneRegToFlash(i, 0);
			ReadWriteRegs[i] = 0;
		}
		else
		{
			ReadWriteRegs[i] = (uint16_t)ReadOneRegFromFlash(i);
		}
	}	
}

uint16_t GetReadWriteRegValue(uint8_t regNum)
{
	if(regNum >= READ_WRITE_REGS_SIZE)
		return 0;
	//return ReadWriteRegs[regNum];
	ReadWriteRegs[regNum] = (*(__IO uint32_t*)( ADDR_FLASH_PAGE_63 + (regNum*4)) );
	return ReadWriteRegs[regNum];
}

uint16_t SetReadWriteRegValue(uint8_t regNum, uint16_t data)
{
	if(regNum >= READ_WRITE_REGS_SIZE)
		return 0;

	uint32_t flashData = (*(__IO uint32_t*)( ADDR_FLASH_PAGE_63 + (regNum*4)) );
	
	ReadWriteRegs[regNum] = data;
	
	if(flashData == 0xFFFFFFFF)
	{
		HAL_FLASH_Unlock();
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ADDR_FLASH_PAGE_63+(regNum*4), (uint32_t)data);
		HAL_FLASH_Lock();
	}
	else
	{
		LoadAllDataFromFlash();
		ReadWriteRegs[regNum] = data;
		
		FLASH_EraseInitTypeDef eraseInitType;
		uint32_t pageError = 0;
		
		// Select banks to erase when Mass erase is enabled. 
		// This parameter must be a value of @ref FLASHEx_Banks
		eraseInitType.Banks = FLASH_BANK_1;	

		// NbPages: Number of pagess to be erased.
    // This parameter must be a value between Min_Data = 1 
		// and Max_Data = (max number of pages - value of initial page)
		eraseInitType.NbPages = 1;

		// PageAdress: Initial FLASH page address to erase when mass erase is disabled
		// This parameter must be a number between Min_Data = 0x08000000 
		// and Max_Data = FLASH_BANKx_END 
		// (x = 1 or 2 depending on devices)
		eraseInitType.PageAddress = ADDR_FLASH_PAGE_63;

		// TypeErase: Mass erase or page erase.
		// This parameter can be a value of @ref FLASHEx_Type_Erase
		eraseInitType.TypeErase = FLASH_TYPEERASE_PAGES;
		
		HAL_FLASH_Unlock();
		HAL_FLASHEx_Erase(&eraseInitType, &pageError);
		HAL_FLASH_Lock();

		HAL_FLASH_Unlock();
		for(uint32_t i = 0; i < READ_WRITE_REGS_SIZE; ++i)
		{
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, ADDR_FLASH_PAGE_63+(i*4), (uint32_t)ReadWriteRegs[i]);
		}
		HAL_FLASH_Lock();

	}
	
	return 1;
}



void LoadAllDataFromFlash(void)
{
	for(uint32_t i = 0; i < READ_WRITE_REGS_SIZE; ++i)
	{
		ReadWriteRegs[i] = (*(__IO uint32_t*)( ADDR_FLASH_PAGE_63 + (i*4)) );
	}
}

//	HAL_FLASH_Lock();
//	HAL_FLASH_Unlock();
//	HAL_FLASH_Lock();
//	FLASH_PageErase(uint32_t PageAddress);
//	FLASH_Program_HalfWord(uint32_t Address, uint16_t Data);
//	HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
//	FLASH_WaitForLastOperation(uint32_t Timeout);
