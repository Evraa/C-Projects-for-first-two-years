#pragma once
#include "Action.h"
class CutAction :
	public Action
{
	Point P;
public:
	CutAction(ApplicationManager *pApp);
	void ReadActionParameters();
	void Execute();
	~CutAction(void);
};

