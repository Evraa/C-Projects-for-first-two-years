#include "DeleteAction.h"
#include "..\ApplicationManager.h"

DeleteAction::DeleteAction(ApplicationManager *pApp): Action (pApp)
{}
void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (pManager ->GetSelectedFig() == NULL)
		pOut ->PrintMessage("Error ,  this action requires a selected figure , first select one");
	else 
		pOut ->PrintMessage("The selected figure was deleted ");
	
}
void DeleteAction:: Execute()
{
	ReadActionParameters();
	if (pManager ->GetSelectedFig() != NULL)
	{
		pManager ->ShiftSelected();            //shifts the selected figure to the end of fig list
		delete pManager->GetSelectedFig();     // deletes the selected fig and makes it equal to NULL so it won't point to the adress of a deleted object
		pManager ->SetSelectedFig(NULL);
		
	}
}
DeleteAction::~DeleteAction(void)
{
}
