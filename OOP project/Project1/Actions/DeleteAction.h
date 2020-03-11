#pragma once
#include "Action.h"
class DeleteAction :public Action
{
	Point P1;
public:
	DeleteAction(ApplicationManager *);
	void ReadActionParameters();
	void Execute();
	~DeleteAction(void);
};

