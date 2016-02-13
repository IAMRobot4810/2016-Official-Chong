#ifndef ROBOTDRIVE_H
#define ROBOTDRIVE_H

class RobotDrive{
private:
	CANTalon* talon1, talon2, talon3, talon4;
	RobotDrive* WoboDrive;
public:
	RobotDrive();
	~RobotDrive();
	void drive_mecanum();


};


#endif
