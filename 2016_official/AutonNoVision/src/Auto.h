#ifndef AUTO_H
#define AUTO_H

#include <WPILib.h>
#include "Shooter.h"
#include "DriveSystem.h"
#include "Defense.h"

class Auto{
private:
	DriveSystem* sys;
	//Defense* def; when developed
	Shooter* sho;

	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	bool targetAcquired;
	enum AutonPos{LEFT, RIGHT, MID};
	enum AutonMode{TERRAIN, ARM, NONE}; //Can't have two enum values as NONE
	AutonMode mode;
	AutonPos pos;
public:
	Auto();
	Auto(int mode, int pos);
	~Auto();

	void CustomAutonChooser();
	void AutonNoVision();

};



#endif /* SRC_AUTO_H_ */
