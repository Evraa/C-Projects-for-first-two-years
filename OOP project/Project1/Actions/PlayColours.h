#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

class PlayColours : public Action
{
	color choosen; // the random color 
	int correct; // the correct choices
	int wrong ; // the wrong choices
	CFigure * fig; // the figure which we play by it's color
	CFigure* Played; // the selected figure the user choose during the game
	int total; // total shapes with the random choosen color
	bool test ;// to continue the game if true
	ActionType Act; // to get the user action
	int x , y ; // to get the user point clicked
	Output* pOut; 
	Input* pIn;  
public:
	PlayColours(ApplicationManager* pApp);//constructor
	//Reads parameters required for action to execute 
	void ReadActionParameters();
	//Execute action 
	void Execute();
	~PlayColours();
};

