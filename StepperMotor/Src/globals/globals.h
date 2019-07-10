#ifndef GLOBALS_H
#define GLOBALS_H

#include "stdint.h"

#define READ_REGS_SIZE				1
#define READ_WRITE_REGS_SIZE	26

extern uint16_t ReadRegs[READ_REGS_SIZE];

extern uint16_t ReadWriteRegs[READ_WRITE_REGS_SIZE];

// Common
#define AsfInterval								ReadWriteRegs[0]
#define PeSignalInv								ReadWriteRegs[1]

// For FBCS
#define StepperFB									ReadWriteRegs[2]
#define LoadingDelayFB						ReadWriteRegs[3]
#define BootSpeedFB								ReadWriteRegs[4]
#define LoadSpeedFB								ReadWriteRegs[5]
#define AlignSpeedFB							ReadWriteRegs[6]
#define AlignLengthFB							ReadWriteRegs[7]
#define LengthFB									ReadWriteRegs[8]
#define LimitSwitchFBInv					ReadWriteRegs[9]
#define HoldingFBDelay						ReadWriteRegs[10]
#define EncStartPrint							ReadWriteRegs[11]
#define StepperFactor							ReadWriteRegs[12]
#define PeEncoder									ReadWriteRegs[13]
#define PlatenEdgeEncoderPosition	ReadWriteRegs[14]

// For PHCS
#define StepperPH									ReadWriteRegs[15]
#define LoadingDelayPH						ReadWriteRegs[16]
#define BootSpeedPH								ReadWriteRegs[17]
#define AlignSpeedPH							ReadWriteRegs[18]
#define SpeedPH1									ReadWriteRegs[19]
#define SpeedPH2									ReadWriteRegs[20]
#define SpeedPH3									ReadWriteRegs[21]
#define AutoSpeedPH								ReadWriteRegs[22]
#define AlignLengthPH							ReadWriteRegs[23]
#define HeigthPH									ReadWriteRegs[24]
#define LimitSwitchPHInv					ReadWriteRegs[25]

uint16_t GetReadRegValue(uint8_t regNum);
uint16_t GetReadWriteRegValue(uint8_t regNum);
uint16_t SetReadWriteRegValue(uint8_t regNum, uint16_t data);

#endif // GLOBALS_H
