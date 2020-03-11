#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
class PasteAction :
	public Action
{
	Point P1;
public:
	PasteAction(ApplicationManager*);
	~PasteAction(void);
	void ReadActionParameters();
	void Execute();
};

