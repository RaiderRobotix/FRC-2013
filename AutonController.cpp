#include "WPILib.h"
#include "AutonController.h"
#include "Constants.h"
#include "HelperFunctions.h"

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
	pickup = Pickup::GetInstance();
	
	m_turnComplete = false;
	m_driveStraightComplete = false;
	
	m_timer = new Timer();
	m_step = 0;
}

void AutonController::Reset() {
	m_step = 0;
}

void AutonController::Test() {
	
	if (m_step == 0) {
		m_driveStraightComplete = drivebase->DriveStraight(200, 2.0, 0.0002);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else {
		drivebase->SetSpeed(0.0);
	}
	
	/*
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
	}*/
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
 * Shoot three from the back of the pyramid.
 * Pick up discs under pyramid.
 */
void AutonController::JimTheWelder() {
	
	printf("Auton Step: %d \n", m_step);
	if (m_step == 0) {
		shooter->Reset();
		shooter->TurnOn();
		drivebase->ResetGyro();
		drivebase->ResetEncoders();
		
		m_timer->Start();
		m_timer->Reset();
		m_step++;
	} else if (m_step == 1) {
		if (m_timer->Get() > 0.5) {
			shooter->Shoot();
		} 
		if (m_timer->Get() > 0.65) {
			shooter->Reset();
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 2) {
		if (m_timer->Get() > 0.5) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 0.65) {
			shooter->Reset();
			
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 3) {
		if (m_timer->Get() > 0.5) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 0.65) {
			shooter->Reset();
			
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 4) {
		pickup->TurnOn();
		shooter->BucketDown();
		shooter->TurnOff();
		m_step++;
	} else if (m_step == 5) {
		drivebase->SetEncoderPID(0.030, 0.0, 0.0);
		m_driveStraightComplete = drivebase->DriveStraight(38, 2.0, 0.0002);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 6) {
		m_turnComplete = drivebase->Turn(-61, 5.0);
		if(m_turnComplete) {
			m_turnComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 7) {
		m_driveStraightComplete = drivebase->DriveStraight(48, 2.0, 0.0002, 0.5);
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 8) {
		m_turnComplete = drivebase->Turn(90.0, 12.0, 0.8);
		if(m_turnComplete) {
			m_turnComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_step++;
		}
	} else if (m_step == 9) {
		m_driveStraightComplete = drivebase->DriveStraight(48, 2.0, 0.0002, 0.5);
		shooter->BucketUp();
		shooter->TiltUp();
		shooter->TurnOn();
		if (m_driveStraightComplete) {
			m_driveStraightComplete = false;
			drivebase->ResetEncoders();
			drivebase->ResetGyro();
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 10) {
		if (m_timer->Get() > 0.5) {
			shooter->Shoot();
		} 
		if (m_timer->Get() > 0.65) {
			shooter->Reset();
			m_timer->Reset();
			m_step++;
		}
	} else if (m_step == 11) {
		if (m_timer->Get() > 0.5) {
			shooter->Shoot();
		}
		if (m_timer->Get() > 0.65) {
			shooter->Reset();
			m_timer->Reset();
			m_step++;
		}
	} else {
		shooter->TurnOff();
		drivebase->SetSpeed(0.0);
	}
}

void AutonController::DoNothing() {
	drivebase->SetSpeed(0.0);
	// TODO: Make other components do nothing.
}
