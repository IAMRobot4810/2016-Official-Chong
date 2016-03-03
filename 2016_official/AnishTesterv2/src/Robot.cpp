#include "WPILib.h"
#include "ImageProcess.h"
#include <vector>
#include <cmath>
#include <algorithm>

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
	ImageProcess process;

	IMAQdxSession session;
	//IMAQdxError error;

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		process.frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		process.binaryFrame = imaqCreateImage(IMAQ_IMAGE_U8, 0);

		process.imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
		if(process.imaqError != IMAQdxErrorSuccess){
			DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)process.imaqError) + "\n");
		}
		process.imaqError = IMAQdxConfigureGrab(session);
		if(process.imaqError != IMAQdxErrorSuccess){
			DriverStation::ReportError("IMAQdxConfigureGram error: " + std::to_string((long)process.imaqError) + "\n");
		}

		//Put default values to SmartDashboard so fields will appear
		SmartDashboard::PutNumber("Tote hue min", process.RING_HUE_RANGE.minValue);
		SmartDashboard::PutNumber("Tote hue max", process.RING_HUE_RANGE.maxValue);
		SmartDashboard::PutNumber("Tote sat min", process.RING_SAT_RANGE.minValue);
		SmartDashboard::PutNumber("Tote sat max", process.RING_SAT_RANGE.maxValue);
		SmartDashboard::PutNumber("Tote val min", process.RING_VAL_RANGE.minValue);
		SmartDashboard::PutNumber("Tote val max", process.RING_VAL_RANGE.maxValue);
		SmartDashboard::PutNumber("Area min %", process.AREA_MINIMUM);
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

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{
		IMAQdxStartAcquisition(session);
	}

	void TeleopPeriodic()
	{
		process.imaqError = IMAQdxGrab(session, process.frame, true, NULL);

		//update threshold values from SmartDashbaord
		process.RING_HUE_RANGE.minValue = SmartDashboard::GetNumber("Tote hue min", process.RING_HUE_RANGE.minValue);
		process.RING_HUE_RANGE.maxValue = SmartDashboard::GetNumber("Tote hue max", process.RING_HUE_RANGE.maxValue);
		process.RING_SAT_RANGE.minValue = SmartDashboard::GetNumber("Tote sat min", process.RING_SAT_RANGE.minValue);
		process.RING_SAT_RANGE.maxValue = SmartDashboard::GetNumber("Tote sat max", process.RING_SAT_RANGE.maxValue);
		process.RING_VAL_RANGE.minValue = SmartDashboard::GetNumber("Tote val min", process.RING_VAL_RANGE.minValue);
		process.RING_VAL_RANGE.maxValue = SmartDashboard::GetNumber("Tote val max", process.RING_VAL_RANGE.maxValue);

		process.imaqError = imaqColorThreshold(process.binaryFrame, process.frame, 255, IMAQ_HSV, &process.RING_HUE_RANGE, &process.RING_SAT_RANGE, &process.RING_VAL_RANGE);

		int numParticles = 0;
		process.imaqError = imaqCountParticles(process.binaryFrame, 1, &numParticles);
		SmartDashboard::PutNumber("Masked paricles", numParticles);


		if(process.imaqError < IMAQdxErrorSuccess){
			DriverStation::ReportError("IMAQdxGram error: " + std::to_string((long)process.imaqError) + "\n");
		}else{
			CameraServer::GetInstance()->SetImage(process.binaryFrame);
		}

		float areaMin = SmartDashboard::GetNumber("Area min %", process.AREA_MINIMUM);
		process.criteria[0] = {IMAQ_MT_AREA_BY_IMAGE_AREA, areaMin, 100, false, false};
		process.imaqError = imaqParticleFilter4(process.binaryFrame, process.binaryFrame, process.criteria, 1, &process.filterOptions, NULL, NULL);


		process.imaqError = imaqCountParticles(process.binaryFrame, 1, &numParticles);
		SmartDashboard::PutNumber("Filtered particles", numParticles);

		if(numParticles > 0){
			std::vector<ImageProcess::ParticleReport_> particles;
			for(int particleIndex = 0; particleIndex < numParticles; particleIndex++){
				ImageProcess::ParticleReport_ par;
				imaqMeasureParticle(process.binaryFrame, particleIndex, 0, IMAQ_MT_AREA_BY_IMAGE_AREA, &(par.PercentAreaToImageArea));
				imaqMeasureParticle(process.binaryFrame, particleIndex, 0, IMAQ_MT_AREA, &(par.Area));
				imaqMeasureParticle(process.binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_TOP, &(par.BoundingRectTop));
				imaqMeasureParticle(process.binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_LEFT, &(par.BoundingRectLeft));
				imaqMeasureParticle(process.binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_BOTTOM, &(par.BoundingRectBottom));
				imaqMeasureParticle(process.binaryFrame, particleIndex, 0, IMAQ_MT_BOUNDING_RECT_RIGHT, &(par.BoundingRectRight));
				particles.push_back(par);

			}
			std::sort(particles.begin(), particles.end(), process.CompareParticleSizes);
			//This example only scores the largest particle. Extending to score all particles and choosing the desired one is left as an exercise
			//for the reader. Note that this scores and reports information about a single particle (single L shaped target). To get accurate information
			//about the location of the tote (not just the distance) you will need to correlate two adjacent targets in order to find the true center of the tote.
			process.scores.Aspect = process.AspectScore(particles.at(0));
			SmartDashboard::PutNumber("Aspect", process.scores.Aspect);
			process.scores.Area = process.AreaScore(particles.at(0));
			SmartDashboard::PutNumber("Area", process.scores.Area);
			bool isTarget = process.scores.Area > process.SCORE_MIN && process.scores.Aspect > process.SCORE_MIN;

			//Send distance and tote status to dashboard. The bounding rect, particularly the horizontal center (left - right) may be useful for rotating/driving towards a tote
			SmartDashboard::PutBoolean("IsTarget", isTarget);
			SmartDashboard::PutNumber("Distance", process.computeDistance(process.binaryFrame, particles.at(0)));

		} else {
			SmartDashboard::PutBoolean("IsTarget", false);
		}



		Wait(0.005);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
