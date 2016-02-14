/*
 * Control.cpp
 *
 *  Created on: Feb 8, 2016
 *      Author: 1750800404
 */

#include "TeleopControl.h"

/*A Button joystick button 0
B Button joystick button 1
X Button joystick button 2
Y Button joystick button 3
L Button joystick button 4
R Button joystick button 5
Back joystick button 6
Start joystick button 7
Left Analog pressed joystick button 8
Right Analog pressed joystick button 9
Left Analog X Axis Joystick Axis, X Axis
Left Analog Y Axis Joystick Axis, Y Axis
Right Analog X Axis Joystick Axis, 4th Axis
Right Analog Y Axis Joystick Axis, 5th Axis*/

TeleopControl::TeleopControl(){

	cont1 = new Joystick(0);
	cont2 = new Joystick(1);
	aButton = new JoystickButton(cont1, 0);
	bButton = new JoystickButton(cont1, 1);
	lStickButton = new JoystickButton(cont1, 8);
	rStickButton = new JoystickButton(cont1, 9);

	drive = new DriveSystem();
	shoot = new Shooter();

	dash = new SmartDashboard();

}

TeleopControl::~TeleopControl(){

	delete cont1;
	delete cont1;
	delete aButton;
	delete bButton;
	delete lStickButton;
	delete rStickButton;
	delete drive;
	delete shoot;
	//delete dash;

}

void TeleopControl::StickDrive(){

	lStickIn = cont1->GetRawAxis(1);
	rStickIn = cont2->GetRawAxis(3);
	lStickScale = pow(lStickIn, 5);
	rStickScale = pow(rStickIn, 5);

	if (lStickIn <= 0.5 && lStickIn >= -0.5){

		drive->Drive(0, rStickScale);

	}

	if (rStickIn <= 0.5 && rStickIn >= -0.5){

		drive->Drive(lStickScale, 0);

	}

	if ((lStickIn > 0.5 || lStickIn < -0.5) && (rStickIn > 0.5 || rStickIn < -0.5)) {

		drive->Drive(lStickScale, rStickScale);

	}

	dash->PutNumber("Left Stick Y Raw", lStickIn);
	dash->PutNumber("Left Stick Y Scaled", lStickScale);
	dash->PutNumber("Right Stick Y Raw", rStickIn);
	dash->PutNumber("Right Stick Y Scaled", rStickScale);

}

void TeleopControl::ButtonControl(){

	if((lStickButton->Get() || rStickButton->Get()) && drive->casterLow == false){

		drive->LowerCasters();

	}

	else if((lStickButton->Get() || rStickButton->Get()) && drive->casterLow == true){

		drive->RaiseCasters();

	}

	if(aButton->Get()){
		shoot->LowGoal(0.25, 100);
	}

	if(bButton->Get()){
		shoot->HighGoal(0.25, 1000);
	}

	//if()

}

void TeleopControl::TriggerControl(){

}
