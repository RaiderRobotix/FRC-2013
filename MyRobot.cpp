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
			
			drivebase->SetEncoderSetpoint(54.0);
			
			if(controls->GetRightButton(4)) {
				drivebase->EnableEncoderPid();
			}
			if(controls->GetRightButton(5)) {
				drivebase->DisableEncoderPid();
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
		float p = -0.05;
		float i = 0.0;
		float d = 0.0;
		float f = 0.0;
		float setpoint = 90;
		
		float increment = 0.00001;
		float speedIncrement = 0.00001;
		
		float absoluteTolerance = 1.0;
		Timer* timer = new Timer();
		bool timerStopped = false;
		
		while (IsTest() && IsEnabled()) {
			// Comment out teleop controls to test PID
			// drivebase->EnableTeleopControls();
			
			if(controls->GetLeftTrigger()) {
				drivebase->ResetEncoders();
			}
			
			// Controls for gyro
			PIDController* gyroController = drivebase->GetGyroController();
			gyroController->SetPID(p, i, d, f);
			gyroController->SetSetpoint(setpoint);
			// gyroController->SetAbsoluteTolerance(5); // DOESN'T WORK
			
			if(gyroController->IsEnabled()) {
				drivebase->SetRightSpeed(-1.0 * gyroController->Get());
			} else {
				drivebase->SetRightSpeed(0.0);
			}
			
			bool onTarget = fabs(gyroController->GetSetpoint() - drivebase->GetGyroAngle()) < absoluteTolerance;
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
			
			if(controls->GetRightTrigger()) {
				drivebase->ResetGyro();
			}
			
			if(controls->GetRightButton(4)) {
				gyroController->Enable();
			}
			if(controls->GetRightButton(5)) {
				gyroController->Disable();
			}
			
			printf("Setpoint: %f \n", gyroController->GetSetpoint());
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Gyro %f          ", drivebase->GetGyroAngle());
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "L: %f            ", drivebase->GetLeftSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "R: %f            ", drivebase->GetRightSpeed());
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Setpoint: %f    ", gyroController->GetSetpoint());
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "P %f I %f", p, i);
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "D %f F %f", d, f);
			dsLCD->UpdateLCD();
			
			// Testing encoder PID control
			if (controls->GetRightTrigger()) {
				p = 0.0;
				i = 0.0;
				d = 0.0;
				f = 0.0;
			}
	
			if (controls->GetLeftButton(3)) {
				p += increment;
			} else if (controls->GetLeftButton(2)) {
				p -= increment;
			}
			
			if (controls->GetLeftButton(9)) {
				i += increment;
			} else if (controls->GetLeftButton(8)) {
				i -= increment;
			}
			
			if (controls->GetRightButton(3)) {
				d += increment;
			} else if (controls->GetRightButton(2)) {
				d -= increment;
			}
			
			if (controls->GetRightButton(9)) {
				f += speedIncrement;
			} else if (controls->GetRightButton(8)) {
				f -= speedIncrement;
			}
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

