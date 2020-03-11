#include "Save.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

//static members initiallized with zero//null//empty

string Save::fullname=" ";
int Save:: SavedTimes=0;

Save::Save(ApplicationManager * pApp) :Action (pApp)
{
	//initiallizing the pointer with zero

	GameFile=NULL;
}


void Save ::ReadActionParameters() 
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	/*
	---this if-cond. to be able to overwrite the exisiting file
	---adding ".txt" to the file name...to make it look better
	*/
	if (SavedTimes==0)
	{
	pOut->PrintMessage("Your game is about to be saved, please Enter your file name :");
	string name = pIn->GetSrting(pOut) ;
	fullname = name +(".txt");
	pOut->ClearStatusBar();
	++SavedTimes;
	}

}
void Save ::Execute() 
{
	ReadActionParameters();
	GameFile = new ofstream (fullname);
	
	//two string to save the current drawing color and filling color

	string CurrentFillColor;
	string CurrentDrawColor;
	
	if (!GameFile->eof())
	{
	//here we get the current drawing color and filling
		CurrentDrawColor = GetColor(UI.DrawColor);
		CurrentFillColor = GetColor(UI.FillColor);
	
	}
	
	//here ,it's been written in the opened file
	*GameFile<<CurrentDrawColor<<" "<<CurrentFillColor<<endl;
	*GameFile<<pManager->getFigCount()<<endl;
	//and then we call saveall func....that is responsible of calling each figure's own save func
	pManager->SaveAll(*GameFile);
	//after all we close the file
	GameFile->close ();
}
Save::~Save()
{
	//checking if the pointer is not equal null to be able to delete it only once
	if (GameFile!=NULL)
		delete GameFile;
}
