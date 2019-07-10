#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"

typedef struct
{
	int32_t steps; //
	void (*SetDir)(uint16_t dir);
	void (*SetEn)(uint16_t en);
	void (*TimerStart)(void);
	void (*TimerStop)(void);
} Motor;

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
