#pragma once
#include "Action.h"
#include "..\DEFS.h"
class DrawingColor :public Action
{
	ActionType ColorAct;
public:
	virtual void ReadActionParameters();
	virtual void Execute();

	DrawingColor(ApplicationManager *pApp);
	
};
