#include "modbus.h"

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
	uint8_t j = 0;
	uint32_t rxLen;
	uint32_t startIndex = 0;
	uint32_t endIndex = 0;
	
	if(receiveFunction(rxBuf, &rxLen) != 0)
	{
		trBuf[j++] = 'R';

		for(i = 0; i < rxLen; ++i)
		{
			//trBuf[i] = rxBuf[i];	
			
			if(rxBuf[i] == PACKET_START_SYMBOL)
			{
				startIndex = i + 1;
			}
			if(rxBuf[i] == PACKET_END_SYMBOL)
			{
				endIndex = i - 1;
			}
		}

		trBuf[j++] = 'C';
		trBuf[j++] = 'H';
		
		
		if(startIndex < endIndex)
		{
		trBuf[j++] = 'I';
		trBuf[j++] = 'N';
		
		trBuf[j++] = 'I';
			if(rxBuf[startIndex] == DEVICE_ID)
			{
				trBuf[j++] = 'I';
				trBuf[j++] = 'D';
				switch(rxBuf[startIndex+1])
				{
					case CMD_READ_READ_REGS:
						trBuf[j++] = 'H';
						break;
					case CMD_READ_RW_REGS:
						trBuf[j++] = 'I';
						break;
					case CMD_WRITE_RW_REGS:
						trBuf[j++] = 'J';
						break;
					default:
						break;					
				};
			}
		}
		transmitFunction(trBuf, j);
	}
	
}

void MakeTransmitPacket(uint8_t *trBuf, uint16_t data)
{
	
}