#include "CopyAction.h"
#include "..\ApplicationManager.h"

CopyAction::CopyAction(ApplicationManager *pApp): Action (pApp)
{}

void CopyAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	if(pManager->GetSelectedFig() == NULL)
		pOut->PrintMessage("Error, this action requires a selected figure , first select one ");
	else 
		pOut->PrintMessage("The selected figure was copied ");


}

void CopyAction::Execute()
{
	ReadActionParameters();
	if(pManager->GetSelectedFig() != NULL)
		pManager->SetClipBoard((pManager->GetSelectedFig())->NewOb());  //sets cipboard to point to the new object made by NewoOb
																		//with the same members of the calling object
	
}