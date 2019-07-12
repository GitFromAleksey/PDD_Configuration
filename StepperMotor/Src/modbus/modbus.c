#include "modbus.h"

// Protocol
// Incoming packet format
// '<','Device_ID','Command','FirstRegAddress','countReadWriteData','>'
// Ansver packet format
// '<','Device_ID','Command','FirstRegAddress','BytesCount','DataBytes','>'

#define DEVICE_ID						11
#define CMD_READ_READ_REGS	0x01
#define CMD_READ_RW_REGS		0x02
#define CMD_WRITE_RW_REGS		0x03
#define PACKET_START_SYMBOL	'<'
#define PACKET_END_SYMBOL		'>'

#define RX_DATA_SIZE  50
#define TX_DATA_SIZE  50

uint8_t trBuf[TX_DATA_SIZE];
uint8_t rxBuf[RX_DATA_SIZE];

uint16_t (*getReadRegValue)(uint8_t regNum);
uint16_t (*getReadWriteRegValue)(uint8_t regNum);
uint16_t (*setReadWriteRegValue)(uint8_t regNum, uint16_t data);
uint8_t  (*transmitFunction)(uint8_t* Buf, uint16_t Len);
int8_t   (*receiveFunction)(uint8_t* Buf, uint32_t *Len);

void MakeTransmitPacket(uint8_t cmd, uint8_t regAddr, uint8_t countReadWrite, uint16_t writeData);

void ModbusInit(uint16_t (*_getReadRegValue)(uint8_t regNum),
								uint16_t (*_getReadWriteRegValue)(uint8_t regNum),
								uint16_t (*_setReadWriteRegValue)(uint8_t regNum, uint16_t data),
								uint8_t (*_transmitFunction)(uint8_t* Buf, uint16_t Len),
								int8_t (*_receiveFunction)(uint8_t* Buf, uint32_t *Len) )
{
	getReadRegValue = _getReadRegValue;
	getReadWriteRegValue = _getReadWriteRegValue;
	setReadWriteRegValue = _setReadWriteRegValue;
	
	transmitFunction = _transmitFunction;
	receiveFunction = _receiveFunction;
}

void ModbusProcess(void)
{
	uint8_t i;
	uint32_t rxLen;
	uint32_t startIndex = 0;
	uint32_t endIndex = 0;
	
	if(receiveFunction(rxBuf, &rxLen) != 0)
	{
		for(i = 0; i < rxLen; ++i)
		{
			if(rxBuf[i] == PACKET_START_SYMBOL)
			{
				startIndex = i + 1;
			}
			if(rxBuf[i] == PACKET_END_SYMBOL)
			{
				endIndex = i - 1;
			}
		}

		if(startIndex < endIndex)
		{
			if(rxBuf[startIndex] == DEVICE_ID)
			{
				MakeTransmitPacket(
					rxBuf[startIndex+1], // command
					rxBuf[startIndex+2], // regAddr
					rxBuf[startIndex+3], // countReadWriteData
					(uint16_t)(rxBuf[startIndex+4]<<8)|rxBuf[startIndex+5]); // uint16_t data
			}
		}
		
	}
	
}

void MakeTransmitPacket(uint8_t cmd, uint8_t regAddr, uint8_t countReadWrite, uint16_t writeData)
{
	int i = 0;

	trBuf[i++] = '<';
	trBuf[i++] = DEVICE_ID;						// Device_ID
	trBuf[i++] = cmd;									// Command
	trBuf[i++] = regAddr;							// FirstRegAddress
	
	switch(cmd)
	{
		case CMD_READ_READ_REGS:
			trBuf[i++] = countReadWrite*2;		// BytesCount
			for(int j = regAddr; j < regAddr + countReadWrite; ++j)
			{
				trBuf[i++] = (uint8_t)(getReadRegValue(j)>>8);
				trBuf[i++] = getReadRegValue(j) & 0xFF;
			}
			trBuf[i++] = '>';
			transmitFunction(trBuf, i);
			break;
		case CMD_READ_RW_REGS:
			trBuf[i++] = countReadWrite*2;		// BytesCount
			for(int j = regAddr; j < regAddr + countReadWrite; ++j)
			{
				trBuf[i++] = (uint8_t)(getReadWriteRegValue(j)>>8);
				trBuf[i++] = getReadWriteRegValue(j) & 0xFF;
			}
			trBuf[i++] = '>';
			transmitFunction(trBuf, i);
			break;
		case CMD_WRITE_RW_REGS:
			setReadWriteRegValue(regAddr, writeData);

			trBuf[i++] = 2;										// BytesCount
			trBuf[i++] = (uint8_t)(getReadWriteRegValue(regAddr)>>8);
			trBuf[i++] = getReadWriteRegValue(regAddr) & 0xFF;
			trBuf[i++] = '>';
			transmitFunction(trBuf, i);
			break;
		default:
			break;					
	};
}
