#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "Controls.h"

class Shooter {

private:
	static Shooter* m_instance;
	Controls* m_controls;
	
	Talon* m_shooterWheel1;
	Talon* m_shooterWheel2;
	
public:
	static Shooter* GetInstance();
	Shooter();
	
	void EnableTeleopControls();
};

#endif
