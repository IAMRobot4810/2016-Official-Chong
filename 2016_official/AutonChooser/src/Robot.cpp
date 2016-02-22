#include "WPILib.h"
#include "Auto.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	//const std::string autoNameCustom = "My Auto";
	const std::string leftSideArm = "Left Side | Arm Defense";
	const std::string leftSideTerrain = "Left Side | Terrain Defense";
	const std::string rightSideArm = "Right Side | Arm Defense";
	const std::string rightSideTerrain = "Right Side | Terrain Defense";
	std::string autoSelected;

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		//chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		chooser->AddObject(leftSideArm, (void*)&leftSideArm);
		chooser->AddObject(leftSideTerrain, (void*)&leftSideTerrain);
		chooser->AddObject(rightSideArm, (void*)&rightSideArm);
		chooser->AddObject(rightSideTerrain, (void*)&rightSideTerrain);
		SmartDashboard::PutData("Auto Modes", chooser);
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == leftSideArm){
			Auto auton(0, 1);
		} else if(autoSelected == leftSideTerrain){
			Auto auton(0, 0);
		} else if(autoSelected == rightSideArm){
			Auto auton(1, 1);
		} else if(autoSelected == rightSideTerrain){
			Auto auton(1, 0);
		} else {
			Auto auton(2, 2);
		}
	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)