#include "Climber.h"

Climber* Climber::m_instance = NULL;

Climber* Climber::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Climber();
  }
  return m_instance;
}

Climber::Climber() {
	m_controls = Controls::GetInstance();
	
	m_climb = new Talon(CLIMB_WINDOW);
	m_rotate = new Talon(CLIMB_CIM);
}

void Climber::EnableTeleopControls() {
	//Raise arms - MOTOR IS SLOW FOR TESTING
	if(m_controls->GetClimberButton(8)){
		m_climb->Set(0.1);
	} else {
		m_climb->Set(0.0);
	}
	
	//Lower arms - MOTOR IS SLOW FOR TESTING
	if(m_controls->GetClimberButton(7)){
		m_climb->Set(-0.1);
	} else {
		m_climb->Set(0.0);
	}
	
	//Raise angle - MOTOR IS SLOW FOR TESTING
	if(m_controls->GetClimberButton(11)){
		m_rotate->Set(0.1);
	} else {
		m_rotate->Set(0.0);
	}
	
	//Lower angle - MOTOR IS SLOW FOR TESTING
	if(m_controls->GetClimberButton(10)){
		m_rotate->Set(0.1);
	} else {
		m_rotate->Set(0.0);
	}
		
}
