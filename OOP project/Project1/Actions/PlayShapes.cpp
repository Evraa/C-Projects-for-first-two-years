#include "PlayShapes.h"

PlayShapes::PlayShapes(ApplicationManager*pApp) : Action ( pApp )
{
	//initializing total and wrong and correct = zero & played & random choice = NULL
	Played = NULL;
	choosen = NULL;
	correct = 0;
	Total = 0;
	wrong = 0;
	//Get a Pointer to the Input / Output Interfaces
    pOut = pManager->GetOutput();
    pIn = pManager->GetInput();
	test = true;  // initiallizing true to continue the game 
}


void PlayShapes :: ReadActionParameters()
{ 
	
	pIn ->GetPointClicked( x , y ); // getting a click from the user
	Act = pIn ->GetUserAction(x , y); // getting the action of the point clicked by the user

	if ( Act == TO_DRAW || Act == PLAY_BOTH || Act == PLAY_CLR || Act == PLAY_SHAPE || Act == EXIT)  // if the user select another action
	{ 
		pManager ->ResetVisibility(); // make all shapes seen if the game is restarted any time
		pManager ->ExecuteAction (Act); //go to applicationmanager to excute the user action
		test = false ; //ending this game
		return ; 
	}
	Played = pManager ->GetFigure( x , y ); //getting the selected figure from the user
}
void PlayShapes :: Execute()
{
	 pManager ->UpdateInterface();  // drawing all shapes seen 

	choosen = pManager->Random( PLAY_SHAPE);
	//case nondrawn shapes
	if ( choosen == NULL )
	{
		pOut ->PrintMessage ( " Please draw some shapes then come to Play :) " );
		return;
	}
	// case playing
	pOut ->PrintMessage ( " select all drawn " + choosen ->Getstring() + " figures to win :D " ) ; //prin msg of the random figure the user will play by

	Total = pManager ->GetCount (  PLAY_SHAPE , choosen ); // calculating the total drawn shapes like the random one

	while ( correct < Total )
{	
	ReadActionParameters(); // getting the user selection

	if ( ! test ) // if false the user takes another action so ending this action
	{	return;   }

	if ( Played != NULL ) // if the user select a shape
	 {
		if ( Played ->Getstring() == choosen ->Getstring() ) // if the selected shape same as the random one
		{ 
			correct++; //No correct will increase
			pOut ->PrintMessage (" Correct One :D ! : correct = " +to_string(correct)+ " wrong = " +to_string(wrong) );	//printing correct and the total correct & wrong
		}
		else 
		{
			wrong ++; // No wrong will increase
			pOut ->PrintMessage ( "Wrong One :( : correct = " +to_string(correct)+ " wrong = " +to_string(wrong) );  //printing wrong and the total correct & wrong
		}

		Played ->setVisiable( false ) ;  // hiding the selected figure 
		pManager ->UpdateInterface();  // redrawing the figlist without the selected figure

	 } // if the user didn't select a shape no thing will happen
}
	// after finishing the game
	pManager ->ResetVisibility();  // Redrawing all the hidden figures
	pOut ->PrintMessage( "Game Finished :D : Total correct = " + to_string ( correct ) + " Total wrong = " + to_string( wrong ) ); // printing the total correct and wrong
	
}

PlayShapes::~PlayShapes()
{

}
