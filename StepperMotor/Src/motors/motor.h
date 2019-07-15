#ifndef MOTOR_H
#define MOTOR_H

#include "stdint.h"

typedef struct
{
	int32_t steps; //
	uint32_t fewSteps;
	uint32_t isFewSteps;
	uint32_t motorSpeed;
	uint32_t motorIsRun;
	uint32_t dir;
	
	// timer callbacks
	void (*setMotorSpeed)(uint32_t speed);
	void (*setOnePulseMode)(void);
	void (*setRunMode)(void);
	void (*timerOnOff)(uint32_t on_off);
	
	// GPIO callbacks
	void (*setMotorEn)(uint32_t en);
	void (*setMotorDir)(uint32_t en);
	
} Motor;

void MotorInit
(
	Motor *motor,
	uint32_t _motorSpeed,
	// timer callbacks
	void (*_setMotorSpeed)(uint32_t speed),
	void (*_setOnePulseMode)(void),
	void (*_setRunMode)(void),
	void (*_timerOnOff)(uint32_t on_off),
	
	// GPIO callbacks
	void (*_setMotorEn)(uint32_t en),
	void (*_setMotorDir)(uint32_t dir)
);

void MotorTakeFewSteps(Motor *motor, uint32_t fewSteps);
void MotorSetOneStepMode(Motor *motor, uint32_t set_reset);
void MotorSetSpeed(Motor *motor, uint32_t speed);
void MotorSetDir(Motor *motor, uint32_t dir);
void MotorReset(Motor *motor);
void MotorStepCounter(Motor *motor);
void MotorStart(Motor *motor);
void MotorStop(Motor *motor);

#endif // MOTOR_H
