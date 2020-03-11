#include "PlayBoth.h"


PlayBoth::PlayBoth(ApplicationManager * pApp ) : Action( pApp )
{
	// initiallizing the total & correct & wrong with zero and the Played and choosen = NULL
	Total = 0;
	correct =0;
	wrong=0;
	choosen = NULL ;
	Played = NULL;
	//Get a Pointer to the Input / Output Interfaces
    pOut = pManager->GetOutput();
    pIn = pManager->GetInput();
	test = true;  // initiallizing true to continue the game 
}

void PlayBoth :: ReadActionParameters() 
{
    pIn ->GetPointClicked(x ,y); // get point cicked by the user
	Act = pIn ->GetUserAction( x , y); // getting the action of the point clicked by the user

	if ( Act == TO_DRAW || Act == PLAY_BOTH || Act == PLAY_CLR || Act == PLAY_SHAPE||Act==EXIT) // if the user select another action
	{ 
			pManager ->ResetVisibility();  // make all shapes seen if the game is restarted any time
			pManager ->ExecuteAction (Act); //go to applicationmanager to excute the user action
			test = false; //ending this game
			return ; 
	}
	Played = pManager ->GetFigure ( x , y ); // getting the selected figure from the user

}

void PlayBoth :: Execute()
{

	pManager ->UpdateInterface(); // drawing all shapes seen

	 choosen = pManager ->Random(  PLAY_BOTH ); // choosing a random figure to play with 

	 // case nonfilled shapes
	if ( choosen == NULL ) 
	{	
		pOut ->PrintMessage( " Please draw some filled shapes then come to enjoy playing :) " );
		return ;
	}

	color CLR = choosen ->GetColour(); // getting the choosen random colour of the shape we play with
	
	pOut ->PrintMessage ( " select all " + GetColor( CLR ) + choosen ->Getstring() + " to win :D " ); // telling the user which colour & shape to play with

	Total = pManager ->GetCount(  PLAY_BOTH , choosen ); // calculating the total shapes with the same colour we play by

// playing with a shape & its colour
	while ( correct < Total )
{	
	ReadActionParameters(); // getting the selected figures from the user

	if ( ! test ) // if false the user takes another action so ending this action
	{	return;   }
	
	if ( Played != NULL ) // if the user select a figure
	{ 
		if ( Played ->GetColour() == choosen ->GetColour() && Played ->Getstring() == choosen ->Getstring() && Played ->IsFilled() ) // if the selected figure and its colour are sililar to the random one
	{ 
		correct++; //No correct increases
		pOut ->PrintMessage (" Correct One :D ! : correct = " +to_string(correct)+ " wrong = " +to_string(wrong) ); //printing correct and the total correct & wrong
	}
	else 
	{
		wrong ++ ; //No wrong increases
		pOut ->PrintMessage ( "Wrong One :( : correct = " +to_string(correct)+ " wrong = " +to_string(wrong) ); //printing wrong and the total correct & wrong
	
	}

		Played->setVisiable( false ) ;  // hidding the selected figure
		pManager ->UpdateInterface();  // redrawing the figlist without the selected figure
	}
}
	// after finishing the game
	pManager ->ResetVisibility(); // making all shapes seen after finishing the game
	pOut ->PrintMessage ( "Game finished :D : Total correct = " + to_string ( correct ) + " Total wrong = " + to_string ( wrong ) );  // printing the No correct & No wrong selected figures
}

PlayBoth::~PlayBoth()
{
}
