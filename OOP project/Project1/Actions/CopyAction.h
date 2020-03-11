#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

class CopyAction : public Action
{
	Point P;
public:
	CopyAction(ApplicationManager*);
	void ReadActionParameters();
	void Execute();
	~CopyAction();

};