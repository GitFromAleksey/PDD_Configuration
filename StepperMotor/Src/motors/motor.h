#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"

typedef struct
{
	void *gpioPort;
	uint16_t pinNumber;
} MotorPin;

typedef struct
{
	int32_t steps; //
//	MotorPin step;
//	MotorPin dir;
//	MotorPin en;
	void (*SetDir)(uint16_t dir);
	void (*SetEn)(uint16_t en);
	void (*TimerStart)(void);
	void (*TimerStop)(void);
} Motor;

void MotorInit(
	Motor *motor, 
//	MotorPin step, 
//	MotorPin dir, 
//	MotorPin en,
	void (*SetDir)(uint16_t dir),
	void (*SetEn)(uint16_t en),
	void (*TimerStart)(void),
	void (*TimerStop)(void)
	);

	void MotorStepCounter(Motor *motor);
	void MotorStart(Motor *motor);
	void MotorStop(Motor *motor);

#endif
