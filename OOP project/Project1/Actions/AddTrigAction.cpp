#include "AddTrigAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\UI_Info.h"

AddTrigAction::AddTrigAction(ApplicationManager * pApp):Action(pApp)
{}

void AddTrigAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first point");
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Triangle: Click at second point");
	pIn->GetPointClicked(P2.x, P2.y);

	pOut->PrintMessage("New Triangle: Click at third point");
	pIn->GetPointClicked(P3.x, P3.y);

	TrigGfxInfo.isFilled =  pManager->getState(); //default is not filled
	//get drawing, filling colors and pen width from the interface
	TrigGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TrigGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddTrigAction::Execute()
{
	ReadActionParameters();
	CTriangle *C=new CTriangle(P1, P2, P3, TrigGfxInfo);
	pManager->AddFigure(C);
}

