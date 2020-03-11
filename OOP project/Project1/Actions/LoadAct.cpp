
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "LoadAct.h"


LoadAct::LoadAct(ApplicationManager * pApp) :Action (pApp)
{
}

void LoadAct :: ReadActionParameters()
{
	int DoIt=0;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearDrawArea();
	

	pOut->PrintMessage("Your game is about to be Loaded, please Enter your file name :");
	/* ---the do-while is used so that if the user enters a false name,,,we ask him to re-enter the name
	    
		---i used the do-while just to ask him at the second time with a different question
	*/
	do
	{
		if (DoIt>0)
		{pOut->PrintMessage("That file doesn't exist, Re-Enter a valid Name :");}

	++DoIt;
	string name = pIn->GetSrting(pOut) ;
	fullname2 = name +(".txt");
	LoadFile.open(fullname2);
	pOut->ClearStatusBar();

	}
	while (!LoadFile.is_open());
	
	pOut->ClearStatusBar();

}


void LoadAct :: Execute()
{
	ReadActionParameters();
	
	string DrawColorLoad, FillColorLoad,DrawnType;
	int figurescount,i=0;
	LoadFile>>DrawColorLoad>>FillColorLoad>>figurescount;
	pManager->Deleting(pManager->getFigCount());
	pManager->setfigcount(0);
	
	
	if (DrawColorLoad=="WHITE")
		UI.DrawColor = WHITE;
	if (DrawColorLoad=="BLUE")
		UI.DrawColor = BLUE;
	if (DrawColorLoad=="GREEN")
		UI.DrawColor = GREEN;	
	if (DrawColorLoad=="RED")
		UI.DrawColor = RED;	
	if (DrawColorLoad=="BLACK")
		UI.DrawColor = BLACK;

	if (FillColorLoad=="WHITE")
		UI.FillColor=WHITE;
	if (FillColorLoad=="RED")
		UI.FillColor=RED;
	if (FillColorLoad=="GREEN")
		UI.FillColor=GREEN;
	if (FillColorLoad=="BLUE")
		UI.FillColor=BLUE;
	if (FillColorLoad=="BLACK")
		UI.FillColor=BLACK;
	
	
	while (i<figurescount)
{
	LoadFile>>DrawnType;
	CFigure* fig;
	/*
	in this implimentation, in order to reduce the coeded lines in app-man and to be aware f th oop logic
	---we create an empty/null/useless instance of specified shape...this object take me to its load
	---there i can specify its coordinates and the app-man add it to the figlist
	*/
	if (DrawnType=="RECT")
	{
	fig = new CRectangle ();
	pManager->LoadThis(LoadFile,fig);
	delete fig;
	}

	if (DrawnType=="CIRCLE")
	{
	fig = new CCircle();
	pManager->LoadThis(LoadFile,fig);
	delete fig;
	}

	if (DrawnType=="TRIANG")
	{
	fig = new CTriangle();
	pManager->LoadThis(LoadFile,fig);
	delete fig;
	}

	if (DrawnType=="LINE")
	{
	fig = new CLine();
	pManager->LoadThis(LoadFile,fig);
	delete fig;
	}

	i++;
}
	LoadFile.close();
}

