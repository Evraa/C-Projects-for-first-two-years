#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"
class PlayBoth : public Action 
{
	int correct ; // the correct choices
	int wrong;  // the wrong choices
	CFigure* choosen; // the random figure we play with 
	CFigure* Played; // the selected figure by the user
	int Total;  // the total figures with color of the selected random figure
	bool test; // to continue the game if true
	ActionType Act; // to get the user action
	int x , y ; // to get the user point clicked
	Output* pOut;
	Input* pIn;
public:
	
	PlayBoth(ApplicationManager* pApp);//constructor
	//Reads parameters required for action to execute 
	void ReadActionParameters();
	//Execute action 
	void Execute();
	
	~PlayBoth(void);
};

