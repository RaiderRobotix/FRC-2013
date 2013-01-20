#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"
#include "Controls.h"

class DriveBase {

private:
	static DriveBase* m_instance;
	
	Controls* m_controls;
	
	// These Victors should be changed to Talons for the actual robot
	Victor* m_leftDrive;
	Victor* m_rightDrive;
	
	Encoder* m_leftEncoder;
	Encoder* m_rightEncoder;
	
	PIDController* m_leftEncoderController;
	PIDController* m_rightEncoderController;
	
	Gyro* m_gyro;
	
	PIDController* m_gyroController;
	
	Timer* m_timer;
	bool m_timerStopped;

public:
	static DriveBase* GetInstance();
	DriveBase();
	void EnableTeleopControls();
	
	void SetSpeed(float speed);
	void SetLeftSpeed(float speed);
	void SetRightSpeed(float speed);
	
	float GetLeftSpeed();
	float GetRightSpeed();
	
	int GetLeftEncoderCount();
	int GetRightEncoderCount();
	void ResetEncoders();
	
	void SetEncoderSetpoint(float inches);
	void EnableEncoderPid();
	void DisableEncoderPid();
	bool EncoderPidIsEnabled();
	
	void ResetGyro();
	float GetGyroAngle();
	void Turn(float setpoint, float tolerance);
	
	// TODO: REMOVE HACK
	PIDController* GetGyroController();
	
	void DriveStraight(float inches, float tolerance);
};

#endif
