#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"

typedef struct
{
	int32_t steps; //
	uint32_t motorSpeed;
	
	// old data
	void (*SetDir)(uint16_t dir);
	void (*SetEn)(uint16_t en);
	void (*TimerStart)(void);
	void (*TimerStop)(void);
	
	// timer callbacks
	void (*setMotorSpeed)(uint32_t speed);
	void (*setOnePulseMode)(void);
	void (*setRunMode)(void);
	void (*timerOnOff)(uint32_t on_off);
	
	// GPIO callbacks
	void (*setMotorEn)(uint32_t en);
	void (*setMotorDir)(uint32_t en);
	
} Motor;

void MotorInit_2
(
	Motor *motor,
	//uint32_t _motorSpeed,
	// timer callbacks
	void (*_setMotorSpeed)(uint32_t speed),
	void (*_setOnePulseMode)(void),
	void (*_setRunMode)(void),
	void (*_timerOnOff)(uint32_t on_off),
	
	// GPIO callbacks
	void (*_setMotorEn)(uint32_t en),
	void (*_setMotorDir)(uint32_t dir)
);

void MotorInit(
	Motor *motor, 
	void (*SetDir)(uint16_t dir),
	void (*SetEn)(uint16_t en),
	void (*TimerStart)(void),
	void (*TimerStop)(void)
	);

	void MotorStepCounter(Motor *motor);
	void MotorStart(Motor *motor);
	void MotorStop(Motor *motor);

#endif // MOTOR_H
