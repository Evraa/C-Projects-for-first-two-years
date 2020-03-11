#ifndef ADD_TRIG_ACTION_H
#define ADD_TRIG_ACTION_H

#include "Action.h"
#include "..\Figures\CTriangle.h"

class AddTrigAction : public Action
{
private:
	Point P1,P2,P3;
	GfxInfo TrigGfxInfo;
public:
	AddTrigAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif

