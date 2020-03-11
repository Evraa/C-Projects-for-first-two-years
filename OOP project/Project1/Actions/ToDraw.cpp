#include "ToDraw.h"


ToDraw::ToDraw(ApplicationManager*pApp) : Action ( pApp )
{
}

void ToDraw ::ReadActionParameters()
{
		//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut ->PrintMessage ( " Drawing Mode On " );
	pOut ->ClearToolBar();
	pOut ->CreateDrawToolBar();
}

void ToDraw ::Execute()
{
	UI.InterfaceMode = MODE_DRAW;
	ReadActionParameters();
}

ToDraw::~ToDraw(void)
{
}
