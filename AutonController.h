#ifndef AUTON_CONTROLLER_H
#define AUTON_CONTROLLER_H

#include "WPILib.h"
#include "DriveBase.h"

class AutonController {
	
private:
	static AutonController* m_instance;
	
	DriveBase* drivebase;
	
	bool m_turnComplete;
	bool m_driveStraightComplete;
	
	Timer* m_timer;
	int m_step;
	
public:
	static AutonController* GetInstance();
	AutonController();
	void Reset();
	
	void Test();
};

#endif