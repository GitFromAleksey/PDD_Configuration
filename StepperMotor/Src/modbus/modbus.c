#include "modbus.h"

#define CMD_READ_READ_REGS	0x01
#define CMD_READ_RW_REGS		0x02
#define CMD_WRITE_RW_REGS		0x03
#define PACKET_START_SYMBOL	'<'
#define PACKET_END_SYMBOL		'>'

uint8_t trBufTmp[10];
uint8_t rxBufTmp[10];

uint8_t *rxBuf;
uint16_t rxBufSize;
uint8_t *txBuf;
uint16_t txBufSize;

uint8_t (*TransmitFunction)(uint8_t* Buf, uint16_t Len);
int8_t (*ReceiveFunction)(uint8_t* Buf, uint32_t *Len);

void ModbusInit( uint8_t (*transmitFunction)(uint8_t* Buf, uint16_t Len),
								int8_t (*receiveFunction)(uint8_t* Buf, uint32_t *Len) )
{
	TransmitFunction = transmitFunction;
	ReceiveFunction = receiveFunction;
}

void ModbusProcess(void)
{
	uint32_t *rxLen;

	if(ReceiveFunction(rxBufTmp, rxLen) != 0)
	{
		for(int i = 0; i < 10; ++i)
		{
			trBufTmp[i] = rxBufTmp[i];
		}

		trBufTmp[7] = 'H';
		trBufTmp[8] = '\r';
		trBufTmp[9] = '\n';
		
		TransmitFunction(trBufTmp, *rxLen);
	}
}
