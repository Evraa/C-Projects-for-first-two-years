#ifndef ADD_LINE_ACTION_H
#define ADD_LINE_ACTION_H

#include "Action.h"
#include "../Figures/CLine.h"


class AddLineAction: public Action
{
private:
	Point P1;
	Point P2;
	GfxInfo LineGfxInfo;
public:
	AddLineAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();	

};

#endif