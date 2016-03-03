#include "WPILib.h"
#include "TeleopControl.h"

#include "Auto.h"



class Robot: public IterativeRobot
{

private:
	LiveWindow *lw = LiveWindow::GetInstance();


	TeleopControl cont;
	Auto* auton;
	Image *camImage;
	int x;
	//double speed;
	DigitalInput *banner;
	CANTalon *tal;

	std::string autoSelected;

	SendableChooser *chooser;
	const std::string auto_noVision = "No Vision - Auton";
	const std::string auto_Vision1 = "Vision; left side terrain - Auton";
	const std::string auto_Vision2 = "Vision; right side terrain - Auton";
	const std::string default_ = "Default - Do Nothing";

	~Robot(){

		delete banner;
		delete tal;
		delete auton;

	}

	void RobotInit()
	{

		/*CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");

		camImage = imaqCreateImage(IMAQ_IMAGE_RGB, 0);*/

		tal = new CANTalon(1);
		banner = new DigitalInput(1);
		//tal->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		x = 0;
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

		if(autoSelected == auto_noVision){
			auton = new Auto();
		} else if (autoSelected == auto_Vision1){
			auton = new Auto(0, 0, true);
		} else if (autoSelected == auto_Vision2) {
			auton = new Auto(0, 1, true);
		}

	}

	void AutonomousPeriodic()
	{

		if(autoSelected == auto_noVision){
			Wait(0.005);
			auton->AutonNoVision();
		} else {
			Wait(15.00); //we have nothing
		}
		Wait(15.00); //when algorithm finishes early

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		cont.StickDrive();
		cont.ButtonControl();
		cont.DashPlace();

		if(cont.cameraFlip == true){
			imaqFlip(camImage, camImage, FlipAxis::IMAQ_HORIZONTAL_AXIS);
		}

		/*for(double i = 0.1; i <= 0.5; i+=0.05){
			tal->Set(i);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.1);
		}

		for(double i = 0.5; i >= 0.1; i-=0.05){
			tal->Set(i);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.1);
		}

		while(speed <= 1.0){
			tal->Set(speed);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.25);
			speed += 0.05;
		}

		while(speed >= 0.0){
			tal->Set(speed);
			SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));
			Wait(0.25);
			speed -= 0.05;
		}

		tal->Set(1.0);

		SmartDashboard::PutNumber("RPM", cont.shoot->ReadRPM(banner, cont.shoot->rpmTimerL, x));*/

		//SmartDashboard::PutNumber("encoder", tal->GetEncPosition());
		//SmartDashboard::PutBoolean("Banner", banner->Get());

		Wait(0.001);

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
