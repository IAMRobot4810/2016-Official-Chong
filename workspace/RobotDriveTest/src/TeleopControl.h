/*
 * Control.h
 *
 *  Created on: Feb 8, 2016
 *      Author: 1750800404
 */

#ifndef TELEOPCONTROL_H
#define TELEOPCONTROL_H

#include "Joystick.h"
#include "SmartDashboard/SmartDashboard.h"
#include "DriveSystem.h"

class TeleopControl{

public:
	TeleopControl();
	~TeleopControl();

	void StickDrive();
	void ButtonControl();
	void TriggerControl();

private:

	Joystick *lStick;
	Joystick *rStick;
	DriveSystem *drive;

	float lStickIn;
	float rStickIn;

	float lStickScale;
	float rStickScale;

protected:

};

#endif /* SRC_CONTROL_H_ */
