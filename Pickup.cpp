#include "WPILib.h"
#include "Pickup.h"
#include "Constants.h"

Pickup* Pickup::m_instance = NULL;

Pickup* Pickup::GetInstance() {
  if (m_instance == NULL) {
    m_instance = new Pickup();
  }
  return m_instance;
}

Pickup::Pickup() {
	m_pickup = new Talon(PICKUP_PWM);
	m_controls = Controls::GetInstance();
}

void Pickup::EnableTeleopControls() {
	if (m_controls->GetShooterButton(6)) { // Spit out
		m_pickup->Set(0.40);
	} else if (m_controls->GetShooterButton(7)) {	// Pick up
		m_pickup->Set(-0.40);
	} else {
		m_pickup->Set(0.0);
	}
}

void Pickup::TurnOn(float speed) {
	m_pickup->Set(-1.0 * speed);
}

void Pickup::TurnOff() {
	m_pickup->Set(0.0);
}
