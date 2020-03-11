#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddTrigAction.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* SelectedFig; //Pointer to the selected figure
	CFigure* Clipboard;   //Pointer to the copied/cut figure
	bool FILL;
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	
public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	void ShiftSelected();                  //shifts the selected figure to the end of the figlist and reduces figcount by one

	// -- Setters &getters
	void SetSelectedFig(CFigure*);
	CFigure * GetSelectedFig()const;
	CFigure* GetClipboard()const;
	void SetClipBoard(CFigure*);

		//PLAY MODE
	bool Isfilled (); // boolean function return true if there is any filled shape in the figlist 
	void ResetVisibility (); // function that make all shapes seen 
	CFigure* Random ( ActionType); // function choose a random figure depends on the actiontype 
	int GetCount(  ActionType , CFigure * fig ); // function that calculate the No shapes of a figure or a figure color depends on the actiontype send to it

	
	//save & load
	void setfigcount (int); //used in loading
	int getFigCount ();      // used  in saving
	void SaveAll (ofstream&);  //the func that is called to save all the figures by class save (pointer of type app-man "pManager" 
	                           //inside class Save)
	void LoadThis (ifstream&,CFigure*);
	void Deleting(int);			//func that is needed  to delete all the added figure after clearing the drawing area

	
	

	
	
		//colors needed functions
	void changeDcolor( color Draw );
	//void changefigureDcolor (color draw);
	void changeFcolor  (color Draw);
	//void changefigureFcolor (color draw);
	void changeState (bool);
	bool getState();

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
	void PrintInfo(CFigure*) const; //prints fig info to the status bar
};

#endif