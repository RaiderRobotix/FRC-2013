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
}

void Climber::EnableTeleopControls() {
	
	
}
