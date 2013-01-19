#include "WPILib.h"
#include "DriveBase.h"
#include "Constants.h"

DriveBase* DriveBase::m_instance = NULL;

DriveBase* DriveBase::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new DriveBase();
  }
  return m_instance;
}

DriveBase::DriveBase() {
	m_controls = Controls::GetInstance();
	
	// Remember to change these to Talons
	m_leftDrive = new Victor(LEFT_DRIVE_PWM);
	m_rightDrive = new Victor(RIGHT_DRIVE_PWM);

	// Encoders
	m_leftEncoder = new Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B);
	m_rightEncoder = new Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B, true);
	
	m_leftEncoder->SetDistancePerPulse(INCHES_PER_COUNT);
	m_rightEncoder->SetDistancePerPulse(INCHES_PER_COUNT);
	
	m_leftEncoderController = new PIDController(0.0, 0.0, 0.0, m_leftEncoder, m_leftDrive);
	m_rightEncoderController = new PIDController(0.0, 0.0, 0.0, m_rightEncoder, m_rightDrive);
	
	m_leftEncoderController->SetPID(ENCODER_P, ENCODER_I, ENCODER_D);
	m_rightEncoderController->SetPID(ENCODER_P, ENCODER_I, ENCODER_D);	
	
	// Gyro
	m_gyro = new Gyro(GYRO_CHANNEL);
	m_gyro->SetSensitivity(GYRO_SENSITIVITY);
	
	m_gyroController = new PIDController(0.0, 0.0, 0.0, m_gyro, m_leftDrive);
}

void DriveBase::EnableTeleopControls() {
	m_leftDrive->Set(m_controls->GetLeftY());
	m_rightDrive->Set(m_controls->GetRightY());
}

void DriveBase::SetSpeed(float speed) {
	m_leftDrive->Set(speed);
	m_rightDrive->Set(speed);
}

void DriveBase::SetLeftSpeed(float speed) {
	m_leftDrive->Set(speed);
}

void DriveBase::SetRightSpeed(float speed) {
	m_rightDrive->Set(speed);
}

float DriveBase::GetLeftSpeed() {
	return m_leftDrive->Get();
}

float DriveBase::GetRightSpeed() {
	return m_rightDrive->Get();
}

int DriveBase::GetLeftEncoderCount() {
	m_leftEncoder->Start();
	return m_leftEncoder->Get();
}

int DriveBase::GetRightEncoderCount() {
	m_rightEncoder->Start();
	return m_rightEncoder->Get();
}

void DriveBase::ResetEncoders() {
	m_leftEncoder->Reset();
	m_rightEncoder->Reset();
}

void DriveBase::SetEncoderSetpoint(float inches) {
	m_leftEncoderController->SetSetpoint(inches);
	m_rightEncoderController->SetSetpoint(inches);
}

void DriveBase::EnableEncoderPid() {
	m_leftEncoderController->Enable();
	m_rightEncoderController->Enable();
}

void DriveBase::DisableEncoderPid() {
	m_leftEncoderController->Disable();
	m_rightEncoderController->Disable();
}

void DriveBase::ResetGyro() {
	m_gyro->Reset();
}

float DriveBase::GetGyroAngle() {
	return m_gyro->GetAngle();
}

PIDController* DriveBase::GetGyroController() {
	return m_gyroController;
}
