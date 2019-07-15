#include "motor.h"

void MotorInit(
	Motor *motor, 

	void (*SetDir)(uint16_t dir),
	void (*SetEn)(uint16_t en),
	void (*TimerStart)(void),
	void (*TimerStop)(void)
	)
{
	motor->steps = 0;
	
	motor->SetDir = SetDir;
	motor->SetEn = SetEn;
	motor->TimerStart = TimerStart;
	motor->TimerStop = TimerStop;
}

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
)
{
	//motor->motorSpeed				= _motorSpeed;
	motor->setMotorSpeed		= _setMotorSpeed;
	motor->setOnePulseMode	= _setOnePulseMode;
	motor->setRunMode				= _setRunMode;
	motor->timerOnOff				= _timerOnOff;
	motor->setMotorEn				= _setMotorEn;
	motor->setMotorDir			= _setMotorDir;
}

// 
void MotorStepCounter(Motor *motor)
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
