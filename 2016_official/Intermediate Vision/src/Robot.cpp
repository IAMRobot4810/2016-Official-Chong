#include "WPILib.h"
#include "NIVision.h"

/**
 * Uses IMAQdx to manually acquire a new image each frame, and annotate the image by drawing
 * a circle on it, and show it on the FRC Dashboard.
 */
class IntermediateVisionRobot : public SampleRobot
{
	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;
	Joystick* stick;
	JoystickButton* a_button;

public:
	void RobotInit() override {
		stick = new Joystick(0);
		a_button = new JoystickButton(stick, 1);
	    // create an image
		frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		//the camera name (ex "cam0") can be found through the roborio web interface
		imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
		}
		imaqError = IMAQdxConfigureGrab(session);
		if(imaqError != IMAQdxErrorSuccess) {
			DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
		}
	}

	void OperatorControl() override {
	    // acquire images
		IMAQdxStartAcquisition(session);

        // grab an image, draw the circle, and provide it for the camera server which will
        // in turn send it to the dashboard.
		while(IsOperatorControl() && IsEnabled()) {
			IMAQdxGrab(session, frame, true, NULL);

			if(a_button->Get()){
				imaqFlip(frame, frame, FlipAxis::IMAQ_HORIZONTAL_AXIS);
			}
			if(imaqError != IMAQdxErrorSuccess) {
				DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
			} else {
				imaqDrawShapeOnImage(frame, frame, { 100, 100, 10, 50 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_RECT, 0.0f);
				CameraServer::GetInstance()->SetImage(frame);
			}
			Wait(0.005);				// wait for a motor update time
		}
        // stop image acquisition
		IMAQdxStopAcquisition(session);
	}
};

START_ROBOT_CLASS(IntermediateVisionRobot)

