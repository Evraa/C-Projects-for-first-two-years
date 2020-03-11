#include "PasteAction.h"


PasteAction::PasteAction(ApplicationManager *pApp): Action (pApp)
{}
void PasteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->GetClipboard() !=NULL )
	{	pOut->PrintMessage("Click on where you want to paste ");  }
	else 
		pOut->PrintMessage("Error, this action requires a selected figure , first select one ");

	pIn->GetPointClicked(P1.x, P1.y);
	pOut->ClearStatusBar();
}
void PasteAction::Execute()
{
	ReadActionParameters();
	if ( pManager->GetClipboard() !=NULL )
		pManager-> AddFigure (pManager->GetClipboard()->Paste(P1));  //call of paste function that 
}
PasteAction::~PasteAction(void)
{
}
