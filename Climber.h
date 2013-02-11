#ifndef CLIMBER_H
#define CLIMBER_H

#include "WPILib.h"
#include "Controls.h"
#include "Constants.h"

class Climber {
private:
	static Climber* m_instance;
	Controls* m_controls;
	
public:
	static Climber* GetInstance();
	Climber();
	
	void EnableTeleopControls();
};

#endif
