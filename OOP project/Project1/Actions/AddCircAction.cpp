#include "AddCircAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"



AddCircAction::AddCircAction(ApplicationManager * pApp):Action(pApp)
{}

void AddCircAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at first point");
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Circle: Click at second point");
	pIn->GetPointClicked(P2.x, P2.y);
	CircGfxInfo.isFilled = pManager->getState();  //default is not filled
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddCircAction::Execute()
{
	ReadActionParameters();
	CCircle *C=new CCircle(P1, P2, CircGfxInfo);
	pManager->AddFigure(C);
}








