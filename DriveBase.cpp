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

	m_leftEncoder = new Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B);
	m_rightEncoder = new Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B, true);
	
	m_leftEncoderController = new PIDController(0.0, 0.0, 0.0, m_leftEncoder, m_leftDrive);
	
	LiveWindow *liveWindow = LiveWindow::GetInstance();
	liveWindow->AddSensor("DriveBase", "Left Encoder", m_leftEncoder);
	liveWindow->AddSensor("DriveBase", "Right Encoder", m_rightEncoder);
}

void DriveBase::EnableTeleopControls() {
	m_leftDrive->Set(m_controls->GetLeftY());
	m_rightDrive->Set(m_controls->GetRightY());
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

PIDController* DriveBase::GetLeftEncoderController() {
	return m_leftEncoderController;
}

/**
 * This must be called since the constructor sets the default PID values to 0.
 */
void DriveBase::SetLeftEncoderPID(float p, float i, float d, float f){
	m_leftEncoderController->SetPID(p, i, d, f);
}

/**
 * Call this after setting up the PID.
 */
void DriveBase::EnableLeftEncoderPID() {
	m_leftEncoderController->Enable();
}

void DriveBase::DisableLeftEncoderPID() {
	m_leftEncoderController->Disable();
}

void DriveBase::SetLeftEncoderSetPoint(float setPoint) {
	m_leftEncoderController->SetSetpoint(setPoint);
}
