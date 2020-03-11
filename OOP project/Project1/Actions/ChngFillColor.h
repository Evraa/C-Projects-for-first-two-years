#pragma once
#include "Action.h"
#include "..\DEFS.h"
class ChngFillColor :public Action
{
	ActionType ColorAct;
public:
	virtual void ReadActionParameters();
	virtual void Execute();

	ChngFillColor(ApplicationManager *pApp);
	
};

