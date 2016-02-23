/*
 * DriveSystem.cpp
 *
 *  Created on: Feb 7, 2016
 *      Author: 1750800404
 */

#include "DriveSystem.h"

DriveSystem::DriveSystem(){
	flTal = new CANTalon(7);
	rlTal = new CANTalon(8);
	frTal = new CANTalon(5);
	rrTal = new CANTalon(6);
	roboDrive = new RobotDrive(flTal, rlTal, frTal, rrTal);
	//Ask about which Talons have to be reversed
	roboDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	roboDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	roboDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	roboDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	roboDrive->SetExpiration(0.1);

	caster = new Solenoid(0, 0);
}

DriveSystem::~DriveSystem(){
	delete flTal;
	delete rlTal;
	delete frTal;
	delete rrTal;
	delete roboDrive;

	delete caster;

}


void DriveSystem::Drive(float left, float right){

	roboDrive->TankDrive(left, right, false);

}

void DriveSystem::LowerCasters(){

	if(casterLow == false){

		caster->Set(false);
		casterLow = true;

	}

}

void DriveSystem::RaiseCasters(){

	if(casterLow == true){

		caster->Set(true);
		casterLow = false;

	}

}
