#include "WPILib.h"
#include "Shooter.h"
#include "Constants.h"

Shooter* Shooter::m_instance = NULL;

Shooter* Shooter::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Shooter();
  }
  return m_instance;
}

Shooter::Shooter() {
	m_shooterWheel1 = new Talon(SHOOTER_BAG_PWM);
	m_shooterWheel2 = new Talon(SHOOTER_775_PWM);
	
	m_controls = Controls::GetInstance();
}

void Shooter::EnableTeleopControls() {
	if (m_controls->GetShooterButton(10)) { // Shoot
		m_shooterWheel1->Set(1.0);
		m_shooterWheel2->Set(1.0);
	} else {
		m_shooterWheel1->Set(0.0);
		m_shooterWheel2->Set(0.0);
	}
}
