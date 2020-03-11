#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"



class PlayShapes : public Action
{
	CFigure* choosen; // the random figure user will play by
	int correct; // No correct choices
	int wrong; //No wrong choices
	int Total; //No total shapes drawn same the selected shape
	CFigure* Played ; // the selected figure the user will enter to play
	bool test ; // to continue the game if true
	ActionType Act; // to get the user action
	int x , y ; // to get the user point clicked
	Output* pOut;
	Input* pIn;
public:
	
	PlayShapes(ApplicationManager *pApp);	//constructor
	//Reads parameters required for action to execute 
	virtual void ReadActionParameters();
	//Execute action 
	virtual void Execute() ;
	~PlayShapes();
};

