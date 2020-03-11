#include "ToPlay.h"


ToPlay::ToPlay(ApplicationManager*pApp) : Action ( pApp )
{
}

void ToPlay ::ReadActionParameters()
{
		//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut ->PrintMessage ( " playing mode is ON please choose a game " );
	pOut ->ClearToolBar();
	pOut ->CreatePlayToolBar();
}

void ToPlay ::Execute()
{
	ReadActionParameters();
	UI.InterfaceMode = MODE_PLAY;
}

ToPlay::~ToPlay(void)
{
}
