#include "AddLineAction.h"
#include "../ApplicationManager.h"
#include "../GUI\Output.h"
#include "../GUI\Input.h"

AddLineAction::AddLineAction(ApplicationManager * pApp): Action(pApp)
{}

void AddLineAction::ReadActionParameters() 
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first point");
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Line: Click at second point");
	pIn->GetPointClicked(P2.x, P2.y);

	LineGfxInfo.isFilled = false; //default is not filled
	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	pOut->ClearStatusBar();

}

void AddLineAction::Execute() 
{
	ReadActionParameters();
	CLine *L=new CLine(P1, P2, LineGfxInfo);
	pManager->AddFigure(L);
}


