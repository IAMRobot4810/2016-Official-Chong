#ifndef AUTO_H
#define AUTO_H

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
	AutonMode mode;
	AutonPos pos;
public:
	Auto();
	Auto(int mode, int pos);
	~Auto();

	void InternalAutonChooser();
	void TerrainCrosser();
	void ArmWallCrosser();
	void SetUpToShoot();
	void Shoot();
	bool Vision();

};



#endif /* SRC_AUTO_H_ */
