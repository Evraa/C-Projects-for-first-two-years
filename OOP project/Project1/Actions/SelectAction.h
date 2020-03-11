#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
class SelectAction : public Action
{
	Point P1;
	CFigure * Temp ;
public:
	SelectAction(ApplicationManager*);
	~SelectAction(void);
	void ReadActionParameters();
	void Execute();
};

