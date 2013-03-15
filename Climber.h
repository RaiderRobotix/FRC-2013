#ifndef CLIMBER_H
#define CLIMBER_H

#include "WPILib.h"
#include "Controls.h"
#include "Constants.h"
#include "Shooter.h"

class Climber {
private:
	static Climber* m_instance;
	Controls* m_controls;
	Talon* m_tilt;
	Talon* m_mast;
	
	AnalogChannel* m_tiltPot;
	AnalogChannel* m_mastPot;
	
	Shooter* shooter;
	
	int m_climbSequenceStep;
	
public:
	static Climber* GetInstance();
	Climber();
	
	void EnableTeleopControls();
	void TiltDownToDrivingPosition();
	void TiltUpToDrivingPosition();
	int GetTiltPot();
	int GetMastPot();
};

#endif
