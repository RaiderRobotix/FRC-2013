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
	
	Timer* timer;

public:
	RobotDemo(void)
	{
		drivebase = DriveBase::GetInstance();
		controls = Controls::GetInstance();
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		
		timer = new Timer();
		
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
		float encoderSetpoint = 300.0;
		float turnSetpoint = 90.0;
		float distanceIncrement = 0.01;
		float increment = 0.00001;
		
		bool timerStopped = false;
		
		while (IsTest() && IsEnabled()) {
			
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
			

			
			// Controls for gyro
			PIDController* gyroController = drivebase->GetGyroController();
			gyroController->SetPID(GYRO_P, GYRO_I, GYRO_D);
			gyroController->SetSetpoint(turnSetpoint);
			
			if(gyroController->IsEnabled()) {
				drivebase->SetRightSpeed(-1.0 * gyroController->Get());
			} else if (!gyroController->IsEnabled() && !drivebase->EncoderPidIsEnabled()) {
				drivebase->SetRightSpeed(0.0);
			}

			bool onTarget = fabs(gyroController->GetSetpoint() - drivebase->GetGyroAngle()) < 2.0;
			if(onTarget) {
				if (timerStopped) {
					timer->Reset();
				}
				timer->Start();
				timerStopped = false;
				if (timer->Get() > 0.5) {
					// TODO: instead of disable, set speed to 0 and make it hold its position.
					gyroController->Disable();
				}
			} else {
				timer->Stop();
				timerStopped = true;
			}
			
			if (controls->GetRightButton(4)) {
				gyroController->Enable();
			}
			if (controls->GetRightButton(5)) {
				gyroController->Disable();
				//drivebase->Turn(turnSetpoint, 2);
			}
			
			drivebase->SetEncoderSetpoint(encoderSetpoint);
			
			if (controls->GetLeftButton(4)) {
				drivebase->EnableEncoderPid();
			}
			if (controls->GetLeftButton(5)) {
				drivebase->DisableEncoderPid();
			}
			
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "L %f, R: %f      ", encoderCountToInches(leftEncoderCount), encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Gyro %f     ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "L: %f R: %f     ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "p: %f    ",  p);
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "setpoint: %f        ", encoderSetpoint);
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "                 ");
			
			dsLCD->UpdateLCD();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

