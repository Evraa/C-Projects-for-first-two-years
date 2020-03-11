#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H

#include "Action.h"
#include  "..\Figures\CCircle.h"

//Add Rectangle Action class
class AddCircAction: public Action
{
private:
	Point P1,P2;
	GfxInfo CircGfxInfo;
public:
	AddCircAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;

};

#endif