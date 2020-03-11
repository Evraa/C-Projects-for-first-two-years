
#pragma once
#include "Action.h"

#include <fstream>
class LoadAct: public Action
{
	ifstream LoadFile;
	string fullname2;

public:

	virtual void ReadActionParameters();
	virtual void Execute();
	LoadAct(ApplicationManager*);
	~LoadAct(void);
};

