#include "SelectAction.h"

#include "..\ApplicationManager.h"

SelectAction::SelectAction(ApplicationManager *pApp): Action (pApp)
{}

void SelectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Click on the shape you want to select ");
	pIn->GetPointClicked(P1.x, P1.y);
	pOut->ClearStatusBar();
}
void SelectAction::Execute()
{
	ReadActionParameters();
	Temp = pManager->GetFigure(P1.x, P1.y);		//if P1 belongs to figure Temp = pointer to that figure equals NULL otherwise
	if (pManager->GetSelectedFig() != NULL)     // if there is already a selected figure
		if (Temp == pManager->GetSelectedFig()) //if the click (P1) belongs to an already selected figure it is unselected
		{
			pManager->GetSelectedFig()->SetSelected(false);
			pManager->SetSelectedFig(NULL);
		}
		else
		{
			if (Temp != NULL)                   //if the click wasn't on an empty area (on a figure other than the already selected)
												//the selected one becomes unselected and the other one that P1 belongs to is selected
			{
				pManager->GetSelectedFig()->SetSelected(false);
				pManager->SetSelectedFig(Temp);
				pManager->GetSelectedFig()->SetSelected(true);
			}
			
		}
	else                                   // there wasn't an already selected figure
	{
		pManager->SetSelectedFig(Temp); // if P1 belongs to figure it is selected and its data member selected is switched to true 
										// and if it doesn't belong to any figure the selectedfig =NULL
		if (pManager->GetSelectedFig() != NULL)
			pManager->GetSelectedFig()->SetSelected(true);
	}
	if (pManager->GetSelectedFig() != NULL)    // if there is a selected shape it prints its info on the status bar
		pManager->PrintInfo(pManager->GetSelectedFig());
}
SelectAction::~SelectAction(void)
{
}
