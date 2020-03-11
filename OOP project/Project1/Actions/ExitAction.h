#pragma once
#include "Action.h"
#include "../ApplicationManager.h"

class ExitAction : public Action
{
public:
 ExitAction(ApplicationManager *);//constructor
	//Reads parameters required for action to execute
 virtual void ReadActionParameters();
 virtual void Execute();
 ~ExitAction();
};

