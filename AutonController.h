#ifndef AUTON_CONTROLLER_H
#define AUTON_CONTROLLER_H

#include "WPILib.h"
#include "DriveBase.h"
#include "Shooter.h"
#include "Pickup.h"
#include "Climber.h"

class AutonController {
	
private:
	static AutonController* m_instance;
	
	DriveBase* drivebase;
	Shooter* shooter;
	Pickup* pickup;
	Climber* climber;
	
	bool m_turnComplete;
	bool m_driveStraightComplete;
	
	Timer* m_timer;
	int m_step;
	
public:
	static AutonController* GetInstance();
	AutonController();
	void Reset();
	
	void Test();
	
	void CliffDey();
	void CliffDey(float shooterSpeed);
	void JimTheWelder();
	void JackTusman();
	void MikeLube();
	void WayneCokeley();
	void ShaunMcNulty();
	
	void DoNothing();
};

#endif
