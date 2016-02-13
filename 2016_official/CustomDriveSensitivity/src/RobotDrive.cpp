#include "RobotDrive.h"

RobotDrive::RobotDrive(){
	talon1 = new CANTalon(0);
	talon2 = new CANTalon(1);
	talon3 = new CANTalon(2);
	talon4 = new CANTalon(3);
	WoboDrive(talon1, talon2, talon3, talon4);
}




RobotDrive::~RobotDrive(){
	delete talon1;
	delete talon2;
	delete talon3;
	delete talon4;
	delete WoboDrive;
}

void RobotDrive::drive_mecanum(){
	WoboDrive->drive_mecanum();
}
