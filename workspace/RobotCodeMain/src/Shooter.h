/*
 * Shooter.h
 *
 *  Created on: Feb 9, 2016
 *      Author: 1750800404
 */

#ifndef SHOOTER_H
#define SHOOTER_H

#include "CANTalon.h"
#include "Solenoid.h"
#include "DigitalInput.h"
#include "Timer.h"

class Shooter{

public:

	Shooter();
	~Shooter();

	bool DetectBall();
	void Pickup(float speed);
	void PickupNoSense(float speed);
	void Raise(float speed);
	void RaiseNoSense(float speed);
	void Lower(float speed);
	void LowerNoSense(float speed);
	void HighGoal(float speed, int encoVal);
	void LowGoal(float speed, int encoVal);
	int ReadRPM(DigitalInput *banner, Timer *Minute, int rpmReading);
	void Shoot(int leftRPM, int rightRPM);
	void ShootNoSense(float leftPow, float rightPow);
	float shooterAngle;

	int lRPMReading;
	int rRPMReading;

private:

	CANTalon *raiseShoot;
	CANTalon *lShooter;
	CANTalon *rShooter;
	CANTalon *picker;

	DigitalInput *lBanner;
	DigitalInput *rBanner;

	Solenoid *shootSol;

	DigitalInput *ballSense;

	Timer *rpmTimerL;
	Timer *rpmTimerR;

	int shooterRestLimit;
	int shooterTopLimit;

protected:

};

#endif /* SRC_SHOOTER_H_ */
