#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"


class ToPlay : public Action
{
public:
	ToPlay( ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
	~ToPlay(void);
};

