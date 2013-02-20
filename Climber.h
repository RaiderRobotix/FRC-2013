#ifndef CLIMBER_H
#define CLIMBER_H

#include "WPILib.h"
#include "Controls.h"
#include "Constants.h"

class Climber {
private:
	static Climber* m_instance;
	Controls* m_controls;
	Talon* m_climb;
	Talon* m_rotate;
	
	AnalogChannel* m_windowPot;
	AnalogChannel* m_cimPot;
	
	Climber* climber;
	
public:
	static Climber* GetInstance();
	Climber();
	
	void EnableTeleopControls();
	int GetWindowPot();
	int GetCimPot();
};

#endif
