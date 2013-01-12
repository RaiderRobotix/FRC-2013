#include "WPILib.h"
#include "DriveBase.h"
#include "Controls.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	DriveBase* drivebase;
	
	DriverStationLCD *dsLCD; 
	DriverStation *driverStation;

public:
	RobotDemo(void)
	{
		drivebase = DriveBase::GetInstance();
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		
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
			
			// Print Encoder Values to Driver station LCD
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", drivebase->GetLeftEncoderValue());
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", drivebase->GetRightEncoderValue());
			dsLCD->UpdateLCD();
			
			GetWatchdog().SetEnabled(false);
			Wait(0.005);				// wait for a motor update time
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

