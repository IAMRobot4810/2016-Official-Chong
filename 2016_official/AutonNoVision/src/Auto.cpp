#include "Auto.h"

Auto::Auto(){
	sys = new DriveSystem();
	sho = new Shooter();

	pos = AutonPos::MID;
	mode = AutonMode::NONE;

	targetAcquired = false;

}

Auto::Auto(int mode_, int pos_, bool vis_check){
	sys = new DriveSystem();
	sho = new Shooter();

	isVision = vis_check;
	mode = static_cast<Auto::AutonMode>(mode_);
	pos = static_cast<Auto::AutonPos>(pos_);

	targetAcquired = false;

}

Auto::~Auto(){
	delete sys;
	delete sho;
}

void Auto::CustomAutonChooser(){


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
	Wait(0.005);
	if(sho->DetectBall()){
		sho->ShootNoSense(1.0, 1.0, 0.5);
		//ahhh
	}else{
		Wait(15.0); //you've done goofed up
	}

}
