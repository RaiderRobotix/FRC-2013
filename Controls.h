#ifndef CONTROLS_H_
#define CONTROLS_H_

#include "WPILib.h"

class Controls {

private:
	static Controls* m_instance;
	Joystick* m_leftStick;
	Joystick* m_rightStick;

public:
	static Controls* GetInstance();
	Controls();
	
	Joystick* GetLeftStick();
	Joystick* GetRightStick();
	
	float GetLeftY();
	float GetRightY();
};
#endif
