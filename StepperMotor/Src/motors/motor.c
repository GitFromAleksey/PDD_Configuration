#include "motor.h"

void MotorInit(
	Motor *motor, 
//	MotorPin step, 
//	MotorPin dir, 
//	MotorPin en,
	void (*SetDir)(uint16_t dir),
	void (*SetEn)(uint16_t en),
	void (*TimerStart)(void),
	void (*TimerStop)(void)
	)
{
	motor->steps = 0;
	
//	motor->step = step;
//	motor->dir = dir;
//	motor->en = en;
	
	motor->SetDir = SetDir;
	motor->SetEn = SetEn;
	motor->TimerStart = TimerStart;
	motor->TimerStop = TimerStop;
}

// 
void StepCounter(Motor *motor)
{
	motor->steps++;
}

void MotorReset(Motor *motor)
{
	motor->steps = 0;
}

void MotorStart(Motor *motor)
{
	motor->SetEn(1);
	motor->TimerStart();
}

void MotorStop(Motor *motor)
{
	motor->TimerStop();
	motor->SetEn(0);
}

int32_t MotorGetSteps(Motor *motor)
{
	return motor->steps;
}
