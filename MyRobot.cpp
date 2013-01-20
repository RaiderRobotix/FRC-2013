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

public:
	RobotDemo(void)
	{
		drivebase = DriveBase::GetInstance();
		controls = Controls::GetInstance();
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		
		GetWatchdog().Kill();
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
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
				drivebase->ResetGyro();
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Gyro: %f     ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "L: %f R: %f     ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->UpdateLCD();
			
			// Wait(0.005);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		float p = 0.1;		
		int encoderSetpoint = 300;
		int distanceIncrement = 1;
		float increment = 0.00001;
		
		while (IsTest() && IsEnabled()) {
			// Comment out teleop controls to test PID
			// drivebase->EnableTeleopControls();
			
			if (controls->GetLeftButton(3)) {
				p += increment;
			}
			if (controls->GetLeftButton(2)) {
				p -= increment;
			}
			
			if (controls->GetRightButton(3)) {
				encoderSetpoint += distanceIncrement;
			}
			if (controls->GetRightButton(2)) {
				encoderSetpoint -= distanceIncrement;
			}
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
				drivebase->ResetGyro();
			}
			
			drivebase->SetEncoderSetpoint(encoderSetpoint);
								
			if(controls->GetRightButton(4)) {
				drivebase->EnableEncoderPid();
				
				// Do corrective stuff to stay straight
				float  error = drivebase->GetGyroAngle();
				
				float leftSpeed = drivebase->GetLeftSpeed() + (error * p);
				float rightSpeed = drivebase->GetRightSpeed() - (error * p);
				
				if (leftSpeed > 1.0) {
					leftSpeed = 1.0;
				} else if (leftSpeed < -1.0) {
					leftSpeed = -1.0;
				}
				
				if (rightSpeed > 1.0) {
					rightSpeed = 1.0;
				} else if (rightSpeed < -1.0) {
					rightSpeed = -1.0;
				}
				
				drivebase->SetLeftSpeed(leftSpeed);
				drivebase->SetRightSpeed(rightSpeed);
			}
			if(controls->GetRightButton(5)) {
				drivebase->DisableEncoderPid();
			}
			
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "L %f, R: %f      ", encoderCountToInches(leftEncoderCount), encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Gyro %f     ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "L: %f R: %f     ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "p: %f    ",  p);
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "setpoint: %d        ", encoderSetpoint);
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "                 ");
			
			dsLCD->UpdateLCD();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

