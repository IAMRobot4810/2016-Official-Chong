#include "Auto.h"

Auto::Auto(){
	sys = new DriveSystem();
	sho = new Shooter();

	pos = AutonPos::NONE;
	mode = AutonMode::NONE_;

	targetAcquired = false;

}

Auto::Auto(int mode_, int pos_){
	sys = new DriveSystem();
	sho = new Shooter();

	mode = static_cast<AutonMode>(mode_);
	pos = static_cast<AutonPos>(pos_);



	targetAcquired = false;

}


Auto::~Auto(){
	delete sys;
	delete sho;
}

void Auto::InternalAutonChooser(){
	if(mode == AutonMode::ARM){
		ArmWallCrosser();
	}else if(mode == AutonMode::TERRAIN){
		TerrainCrosser();
	}else{
		Wait(15.0); //you've done goofed up
	}

}

void Auto::ArmWallCrosser(){


}

void Auto::TerrainCrosser(){


}

void Auto::SetUpToShoot(){
	Wait(0.1);
	sys->LowerCasters();

	if(sho->DetectBall()){
		while(!targetAcquired){
			if(pos == AutonPos::LEFT){
				sys->Drive(0.0, 0.1);//sweep right
				Vision(); //dummy vision

			}else if(pos == AutonPos::RIGHT){
				sys->Drive(0.1, 0.0);
				Vision();
			}else{
				break; //AutonPos error
			}

		}
		Wait(0.1);
		sys->RaiseCasters();
	}else{
		Wait(10.0); //wait for teleop. you've done goofed up
	}
	if(pos == AutonPos::NONE){
		Wait(10.0); //you've done goofed up
	}
	sho->Raise(0.25);

}

void Auto::Shoot(){
	sho->Shoot(5000, 5000);
	sho->Lower(0.25);
}

bool Auto::Vision(){
	if(false){
		targetAcquired = true;
	}
	return targetAcquired;
}
