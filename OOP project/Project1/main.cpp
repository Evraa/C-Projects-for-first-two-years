#include "ApplicationManager.h"
string GetColor (color CLr ) // function return string of the color name
{ 
 if ( CLr == RED )
	 return "RED";
 if ( CLr == WHITE )
	 return "WHITE" ;
 if ( CLr == GREEN )
	 return "GREEN" ;
 if ( CLr == BLACK )
	 return "BLACK" ;
 if ( CLr == BLUE )
	 return "BLUE";
}

int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);
	

	
	return 0;
}