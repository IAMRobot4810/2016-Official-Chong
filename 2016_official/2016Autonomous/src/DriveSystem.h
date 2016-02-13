/*
 * DriveSystem.h
 *
 *  Created on: Feb 7, 2016
 *      Author: 1750800404
 */

#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include "CANTalon.h"
#include "RobotDrive.h"
#include "Solenoid.h"

class DriveSystem{

public:
	DriveSystem();
	~DriveSystem();

	void Drive(float left, float right);
	void LowerCasters();
	void RaiseCasters();


private:

	CANTalon *flTal;
	CANTalon *rlTal;
	CANTalon *frTal;
	CANTalon *rrTal;
	RobotDrive *roboDrive;

	Solenoid *caster;

	bool casterLow;

protected:

};

#endif /* SRC_DRIVESYSTEM_H_ */
