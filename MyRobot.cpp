#include "WPILib.h"
#include "DriveBase.h"
#include "Controls.h"
#include "HelperFunctions.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	DriveBase* drivebase;
	Controls* controls;
	
	DriverStationLCD* dsLCD; 
	DriverStation* driverStation;
	LiveWindow* liveWindow;

public:
	RobotDemo(void)
	{
		drivebase = DriveBase::GetInstance();
		controls = Controls::GetInstance();
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		liveWindow = LiveWindow::GetInstance();
		
		GetWatchdog().SetEnabled(false);
	}

	/**
	 * TODO: Win.
	 */
	void Autonomous(void)
	{
		while (IsAutonomous() && IsEnabled()) {
			
		}
	}

	/**
	 * TODO
	 */
	void OperatorControl(void)
	{
		while (IsOperatorControl() && IsEnabled())
		{
			drivebase->EnableTeleopControls();
			
			GetWatchdog().SetEnabled(false);
			// Wait(0.005);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		PIDController* leftEncoderController = drivebase->GetLeftEncoderController();
		
		while (IsTest() && IsEnabled()) {
			// Try commenting this out to see if it conflicts with PID.
			// drivebase->EnableTeleopControls();
			
			// Print Encoder Values to Driver station LCD
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
			}
						
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));
			dsLCD->UpdateLCD();
			
			// Testing encoder PID control
			if (controls->GetRightTrigger()){
				float p = 0.01;
				float i = 0.0;
				float d = 0.0;
				float f = 0.1; // feed forwad speed
				leftEncoderController->SetPID(p, i, d, f);
				leftEncoderController->SetSetpoint(256.0);
				leftEncoderController->Enable();
				
				printf("PID Enabled %s\n", leftEncoderController->IsEnabled() ? "true" : "false");
			}
			if (controls->GetRightButton(2)) {
				drivebase->DisableLeftEncoderPID();
				printf("PID Disabled\n");
			}
			
			
			liveWindow->Run();
			GetWatchdog().SetEnabled(false);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

