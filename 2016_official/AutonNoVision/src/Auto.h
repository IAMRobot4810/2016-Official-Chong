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


	bool targetAcquired;
	enum AutonPos{LEFT, RIGHT, MID};
	enum AutonMode{TERRAIN, ARM, NONE}; //Can't have two enum values as NONE
	bool isVision;
	AutonMode mode;
	AutonPos pos;
public:
	Auto();
	Auto(int mode, int pos, bool vis_check);
	~Auto();

	void CustomAutonChooser();
	void AutonNoVision();

};



#endif /* SRC_AUTO_H_ */