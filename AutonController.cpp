#include "WPILib.h"
#include "AutonController.h"
#include "Constants.h"

AutonController* AutonController::m_instance = NULL;

AutonController* AutonController::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new AutonController();
  }
  return m_instance;
}

AutonController::AutonController() {
	drivebase = DriveBase::GetInstance();
	shooter = Shooter::GetInstance();
	
	m_turnComplete = false;
	m_driveStraightComplete = false;
	
	m_timer = new Timer();
	m_step = 0;
}

void AutonController::Reset() {
	m_step = 0;
}

void AutonController::Test() {
	
	float turnTolerance = 2.0;
	float driveStraightTolerance = 3.0;
	
	if (m_step == 0) {
		m_driveStraightComplete = drivebase->DriveStraight(89.0, driveStraightTolerance, DRIVE_STRAIGHT_P);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 1) {
		m_turnComplete = drivebase->Turn(80, turnTolerance);
		if(m_turnComplete) {
			m_turnComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 2) {
		m_driveStraightComplete = drivebase->DriveStraight(-130, driveStraightTolerance, DRIVE_STRAIGHT_P);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 3) {
		m_turnComplete = drivebase->Turn(-105, turnTolerance);
		if(m_turnComplete) {
			m_turnComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else {
		drivebase->SetSpeed(0.0);
	}
}

/**
 * Sit and shoot three from the back of the pyramid.
 * Grab the discs under the pyramid.
 */
void AutonController::CliffDey() {
	if (m_step == 0) {
		shooter->Reset();
		shooter->TurnOn();
		
		m_timer->Start();
		m_timer->Reset();
		m_step++;
	} else if (m_step == 1) {
		if (m_timer->Get() > 1.0) {
			shooter->Shoot();
		} 
		if (m_timer->Get() > 1.15) {
			shooter->Reset();
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 2) {
		if (m_timer->Get() > 1.0) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 1.15) {
			shooter->Reset();
			
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 3) {
		if (m_timer->Get() > 1.0) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 1.15) {
			shooter->Reset();
			
			m_timer->Reset();
			m_step++;
		}
	} else {
		shooter->TurnOff();
	}
}

/**
 * Shoot three from the back of the pyramid
 */
void AutonController::JimTheWelder() {
	if (m_step == 0) {
		shooter->Reset();
		shooter->TurnOn();
		
		m_timer->Start();
		m_timer->Reset();
		m_step++;
	} else if (m_step == 1) {
		if (m_timer->Get() > 1.0) {
			shooter->Shoot();
		} 
		if (m_timer->Get() > 1.15) {
			shooter->Reset();
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 2) {
		if (m_timer->Get() > 1.0) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 1.15) {
			shooter->Reset();
			
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 3) {
		if (m_timer->Get() > 1.0) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 1.15) {
			shooter->Reset();
			
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 4) {
		
	} else {
		shooter->TurnOff();
	}
}

void AutonController::DoNothing() {
	drivebase->SetSpeed(0.0);
	// TODO: Make other components do nothing.
}
