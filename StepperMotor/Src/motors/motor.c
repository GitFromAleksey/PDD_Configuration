#include "motor.h"

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
)
{
	motor->motorSpeed = _motorSpeed;
	
	motor->dir = 0;

	motor->setMotorSpeed		= _setMotorSpeed;
	motor->setOnePulseMode	= _setOnePulseMode;
	motor->setRunMode				= _setRunMode;
	motor->timerOnOff				= _timerOnOff;
	motor->setMotorEn				= _setMotorEn;
	motor->setMotorDir			= _setMotorDir;
	
	motor->motorIsRun = 0;
	motor->isFewSteps = 0;
	motor->setMotorSpeed(_motorSpeed);
	motor->timerOnOff(0);
	motor->steps = 0; //
}

void MotorTakeFewSteps(Motor *motor, uint32_t fewSteps)
{
	motor->fewSteps = fewSteps;
	motor->isFewSteps = 1;
	MotorStart(motor);
}

void MotorSetOneStepMode(Motor *motor, uint32_t set_reset)
{
	if(set_reset > 0)
	{
		motor->setOnePulseMode();
	}
	else
	{
		motor->setRunMode();
	}
}

void MotorSetSpeed(Motor *motor, uint32_t speed)
{
	motor->motorSpeed	= speed;
	motor->setMotorSpeed(speed);
}

void MotorSetDir(Motor *motor, uint32_t dir)
{
	motor->setMotorDir(dir);
	motor->dir = dir;
}

void MotorStepCounter(Motor *motor)
{
	if(motor->dir == 0)
		motor->steps++;
	else
		motor->steps--;
	
	
	if(motor->isFewSteps)
	{
		if(--motor->fewSteps == 0)
		{
			motor->isFewSteps = 0;
			MotorStop(motor);
		}
	}
}

void MotorReset(Motor *motor)
{
	motor->setMotorEn(0);
	motor->setMotorDir(0);
	motor->timerOnOff(0);
	motor->steps = 0;
	motor->motorIsRun = 0;
}

void MotorStart(Motor *motor)
{
	motor->setMotorEn(1);
	motor->timerOnOff(1);
	motor->motorIsRun = 1;
}

void MotorStop(Motor *motor)
{
	motor->timerOnOff(0);
	motor->setMotorEn(0);
	motor->motorIsRun = 0;
}
