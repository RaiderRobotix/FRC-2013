#ifndef PICKUP_H
#define PICKUP_H

#include "WPILib.h"
#include "Controls.h"

class Pickup {

private:
	static Pickup* m_instance;
	Talon* m_pickup;
	Controls* m_controls;
	
public:
	static Pickup* GetInstance();
	Pickup();
	
	void EnableTeleopControls();
	void TurnOn(float speed = 0.5);
	void TurnOff();
};

#endif
