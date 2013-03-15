#include "Climber.h"

Climber* Climber::m_instance = NULL;

Climber* Climber::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Climber();
  }
  return m_instance;
}

//static const int WINDOW_MAX = ???, WINDOW_MIN = ???;
//static const int CIM_MAX = ???, CIM_MIN = ???;

Climber::Climber() {
	m_controls = Controls::GetInstance();
	
	m_tilt = new Talon(CLIMB_WINDOW);
	m_mast = new Talon(CLIMB_CIM);
	
	m_tiltPot = new AnalogChannel(TILT_POT_CHAN);
	m_mastPot = new AnalogChannel(MAST_POT_CHAN);
	
	m_climbSequenceStep = 0;
}

void Climber::EnableTeleopControls() {
	// MAST
	int mastPosition = m_mastPot->GetValue();
	int lowerMastLimit = 57; // 57 for climbing, 67 for manual
	int upperMastLimit = 880;

	// TILT
	int forwardTiltLimit = 630;
	int backTiltLimit = 430;
	
	float tiltSpeed = m_controls->GetClimberY();
	int tiltPosition = m_tiltPot->GetValue();
	
	// Reset Climbing Sequence
	if (m_controls->GetClimberButton(9)) {
		m_climbSequenceStep = 0;
	}
	
	if (m_controls->GetClimberButton(3) && mastPosition < upperMastLimit) {
		m_mast->Set(1.0);
	} else if (m_controls->GetClimberButton(2) && mastPosition > lowerMastLimit) {
		m_mast->Set(-1.0);
	} else if (m_controls->GetShooterButton(8)) {
		TiltDownToDrivingPosition();
	} else if (m_controls->GetShooterButton(9)) {
		TiltUpToDrivingPosition();
	} else if (tiltSpeed < -0.1 && tiltPosition < forwardTiltLimit) {
		m_tilt->Set(tiltSpeed);
	} else if (tiltSpeed > 0.1 && tiltPosition > backTiltLimit) {
		m_tilt->Set(tiltSpeed);
	} else if (m_controls->GetClimberButton(6)) { 					// TILT TO LEVEL 1
		if (tiltPosition < 486) {
			m_tilt->Set(-1.0);
		} else {
			m_tilt->Set(0.0);
		}
	} else if (m_controls->GetClimberButton(7)) {		// RAISE MAST TO READY LEVEL 1 CLIMB
		if (mastPosition < 406) {
			m_mast->Set(1.0);
		} else {
			m_mast->Set(0.0);
		}
	} else if (m_controls->GetClimberButton(8)) {
		if (m_climbSequenceStep == 0) {			
			if (mastPosition > 58) {
				m_mast->Set(-1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 1) {
			if (tiltPosition < 526) {
				m_tilt->Set(-1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 2) {
			if (mastPosition < 72) {
				m_mast->Set(1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 3) {
			if (tiltPosition < 560) {
				m_tilt->Set(-1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 4) {
			if (mastPosition < 878) {
				m_mast->Set(1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 5) {
			if (tiltPosition > 550) {
				m_tilt->Set(1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 6) {
			if (mastPosition > 610) {
				m_mast->Set(-1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 7) {
			if (tiltPosition < 605) {
				m_tilt->Set(-1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 8) {
			if (mastPosition > 152) {
				m_mast->Set(-1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 9) {
			if (tiltPosition > 544) {
				m_tilt->Set(1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 10) {
			if (mastPosition < 172) {
				m_mast->Set(1.0);
			} else {
				m_mast->Set(0.0);
				m_climbSequenceStep++;
			}
		} else if (m_climbSequenceStep == 11) {
			if (tiltPosition > 516) {
				m_tilt->Set(1.0);
			} else {
				m_tilt->Set(0.0);
				m_climbSequenceStep++;
			}
		} else {
			m_mast->Set(0.0);
			m_tilt->Set(0.0);
		}
	}
	else {
		m_tilt->Set(0.0);
		m_mast->Set(0.0);
	}
}

void Climber::TiltDownToDrivingPosition() {
	int tiltPosition = m_tiltPot->GetValue();
	int targetPosition = 430;
	int position1 = targetPosition + 30;
	int position2 = targetPosition + 20;
	int position3 = targetPosition + 10;
	
	if (tiltPosition > position1) {
		m_tilt->Set(1.0);
	} else if (tiltPosition <= position1 && tiltPosition > position2 ) {
		m_tilt->Set(0.7);
	} else if (tiltPosition <= position2 && tiltPosition > position3) {
		m_tilt->Set(0.5);
	} else if (tiltPosition <= position3 && tiltPosition > targetPosition) {
		m_tilt->Set(0.2);
	} else {
		m_tilt->Set(0.0);
	}
}

void Climber::TiltUpToDrivingPosition() {
	int tiltPosition = m_tiltPot->GetValue();
	int targetPosition = 483;
	int position3 = targetPosition - 10;
	int position2 = targetPosition - 20;
	int position1 = targetPosition - 30;
	
	if (tiltPosition < position1) {
		m_tilt->Set(-1.0);
	} else if (tiltPosition >= position1 && tiltPosition < position2 ) {
		m_tilt->Set(-0.7);
	} else if (tiltPosition >= position2 && tiltPosition < position3) {
		m_tilt->Set(-0.5);
	} else if (tiltPosition >= position3 && tiltPosition < targetPosition) {
		m_tilt->Set(-0.2);
	} else {
		m_tilt->Set(0.0);
	}
}

int Climber::GetTiltPot(){
	return m_tiltPot->GetValue();
}

int Climber::GetMastPot(){
	return m_mastPot->GetValue();
}
