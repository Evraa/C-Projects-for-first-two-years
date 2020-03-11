#include "CutAction.h"
#include "..\ApplicationManager.h"


CutAction::CutAction(ApplicationManager *pApp): Action (pApp)
{}

void CutAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	if(pManager->GetSelectedFig() == NULL)
		pOut->PrintMessage("Error,  this action requires a selected figure , first select one");
	else 
		pOut->PrintMessage("The selected figure was cut ");

}

void CutAction::Execute()
{
	ReadActionParameters();
	if(pManager->GetSelectedFig() != NULL)
	{
		pManager->SetClipBoard((pManager->GetSelectedFig())->NewOb());  //sets cipboard to point to the new object made by NewoOb
																		//with the same members of the calling object
		pManager->ShiftSelected();                                      //shifts the selected figure to the end of fig list
		delete pManager->GetSelectedFig();        // deletes the selected fig and makes it equal to NULL so it won't point to the adress of a deleted object
		pManager->SetSelectedFig(NULL);
	}
}

CutAction::~CutAction(void)
{
}
