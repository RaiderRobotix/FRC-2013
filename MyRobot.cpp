#include "WPILib.h"
#include "DriveBase.h"
#include "Pickup.h"
#include "Shooter.h"
#include "Climber.h"
#include "Controls.h"
#include "HelperFunctions.h"
#include "AutonController.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	AutonController* autonController;
	
	DriveBase* drivebase;
	Pickup* pickup;
	Shooter* shooter;
	Controls* controls;
	
	DriverStationLCD* dsLCD; 
	DriverStation* driverStation;
	
	Timer* timer;
	
	SendableChooser *autonSelector;

public:
	RobotDemo(void)
	{
		autonController = AutonController::GetInstance();
		
		drivebase = DriveBase::GetInstance();
		pickup = Pickup::GetInstance();
		shooter = Shooter::GetInstance();
		controls = Controls::GetInstance();
		
		dsLCD = DriverStationLCD::GetInstance();
		driverStation = DriverStation::GetInstance();
		
		timer = new Timer();
		
		autonSelector = new SendableChooser();
		autonSelector->AddObject("Test", (void*)1);
		autonSelector->AddDefault("Do Nothing", (void*)0);
		
		SmartDashboard::init();
		SmartDashboard::PutData("Autonomous Mode", autonSelector);
		
		GetWatchdog().Kill();
	}

	/**
	 * TODO: Win.
	 */
	void Autonomous(void)
	{
		int selectedAutoMode = (int)(autonSelector->GetSelected());
		
		while (IsAutonomous() && IsEnabled()) 
		{	
			switch (selectedAutoMode) {
				case 0: autonController->DoNothing(); break;
				case 1: autonController->Test(); break;
			}
			
			// Print Encoder Values to Driver station LCD
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			// For Debug Purposes
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Left Enc %d      ", leftEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Right Enc %d     ", rightEncoderCount);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Left In. %f      ", encoderCountToInches(leftEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Right In. %f     ", encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Gyro: %f         ", drivebase->GetGyroAngle());
			//dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "L: %f R: %f      ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "Auto: %d            ", (int)(autonSelector->GetSelected()));
			dsLCD->UpdateLCD();
		}
	}

	/**
	 * TODO
	 */
	void OperatorControl(void)
	{
		while (IsOperatorControl() && IsEnabled())
		{	
			autonController->Reset();
			drivebase->EnableTeleopControls();
			pickup->EnableTeleopControls();
			shooter->EnableTeleopControls();
			
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
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Gyro: %f         ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "L: %f R: %f      ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->UpdateLCD();
			
			// Wait(0.005);
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		float p = 0.0;
		float i = 0.0;
		float d = 0.0;
		
		float encoderSetpoint = 200.0;
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
			
			if (controls->GetLeftButton(8)) {
				i += increment;
			}
			if (controls->GetLeftButton(9)) {
				i -= increment;
			}
			
			if (controls->GetRightButton(3)) {
				d += increment;
			}
			if (controls->GetRightButton(2)) {
				d -= increment;
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
			gyroController->SetPID(p, i, d);
			
			//gyroController->SetPID(GYRO_P, GYRO_I, GYRO_D);
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
			//drivebase->SetEncoderPID(p,i,d);
			
			if (controls->GetLeftButton(4)) {
				//drivebase->EnableEncoderPid();
				drivebase->DriveStraight(encoderSetpoint, 2.0, DRIVE_STRAIGHT_P);
			}
			if (controls->GetLeftButton(5)) {
				drivebase->DisableEncoderPid();
			}
			
			int leftEncoderCount = drivebase->GetLeftEncoderCount();
			int rightEncoderCount = drivebase->GetRightEncoderCount();
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "L %f, R: %f      ", encoderCountToInches(leftEncoderCount), encoderCountToInches(rightEncoderCount));
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Gyro %f     ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "L: %f R: %f        ",  drivebase->GetLeftSpeed(), drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "p: %f              ",  p);
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "i: %f              ", i);
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "d: %f              ", d);
			
			dsLCD->UpdateLCD();
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

