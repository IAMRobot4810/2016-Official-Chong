#include "Auto.h"

Auto::Auto(){
	sys = new DriveSystem();
	sho = new Shooter();

	pos = AutonPos::MID;
	mode = AutonMode::NONE;

	targetAcquired = false;

}

Auto::Auto(int mode_, int pos_){
	sys = new DriveSystem();
	sho = new Shooter();

	//mode = mode_;
	//pos = pos_;

	targetAcquired = false;

}

void Auto::AutonNoVision(){
	//move past the low bar
	sys->Drive(0.5, 0.5);
	Wait(1.0);
	//line up to shoot
	sys->Drive(0.0, 0.0);
	Wait(0.005);
	sys->Drive(0.0, 0.25);
	Wait(1.0);
	//shoot
	sys->Drive(0.0, 0.0);
	sho->ShootNoSense(1.0, 1.0, 0.5);
}

