#pragma once

#include "Action.h"
#include "..\ApplicationManager.h"

class ToDraw : public Action
{
public:
	ToDraw( ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
	~ToDraw(void);
};

