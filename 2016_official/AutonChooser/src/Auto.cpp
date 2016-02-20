#include "Auto.h"

Auto::Auto(){

	pos = AutonPos::NONE;
	mode = AutonMode::NONE_;

	targetAcquired = false;

}

Auto::Auto(int mode_, int pos_){

	mode = static_cast<AutonMode>(mode_);
	pos = static_cast<AutonPos>(pos_);

	SmartDashboard::PutNumber("AutonMode", static_cast<double>(mode));
	SmartDashboard::PutNumber("AutonPos", static_cast<double>(pos));

	targetAcquired = false;

}


Auto::~Auto(){

}


