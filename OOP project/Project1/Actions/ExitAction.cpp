#include "ExitAction.h"



ExitAction::ExitAction(ApplicationManager *pApp) : Action(pApp)
{

}
void ExitAction :: ReadActionParameters()
{
		Output* pOut = pManager->GetOutput();
	if(UI.InterfaceMode == MODE_PLAY)
		pOut->PrintMessage("are you sure you want to exit? click exit");
}

void ExitAction:: Execute() 
{
	ReadActionParameters();

}

ExitAction::~ExitAction()
{
	
}

