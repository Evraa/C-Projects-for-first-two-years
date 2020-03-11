#include "PlayColours.h"


PlayColours::PlayColours(ApplicationManager * pApp ) : Action( pApp )
{
	// initiallizing total shapes and correct ans wrong = 0 and pOut 
	total = 0;
	correct =0;
	wrong=0;
	//Get a Pointer to the Input / Output Interfaces
    pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	test = true;  // initiallizing true to continue the game 
}

void PlayColours :: ReadActionParameters()
{
	pIn ->GetPointClicked(x ,y); //getting a click from the user
	Act = pIn ->GetUserAction(x , y); // check the action of this point click 
	if (Act == TO_DRAW || Act == PLAY_BOTH || Act == PLAY_CLR || Act == PLAY_SHAPE || Act == EXIT)  // if the user select another action
	{ 
		pManager ->ResetVisibility();  // make all shapes seen if the game is restarted any time
		pManager ->ExecuteAction ( Act ); //go to applicationmanager to excute the user action
		test = false; //ending this game
		return ; 
	}
	Played = pManager ->GetFigure ( x , y ); //getting the selected figure from the user

}

void PlayColours :: Execute()
{

	pManager ->UpdateInterface(); // drawing all shapes seen 

	// making the random choice to play 
	 fig = pManager ->Random( PLAY_CLR); // getting filled shape to play with it's color

	 // case of nonfilled colours printing msg to draw some filled figures then come to play
	if ( fig == NULL ) 
	{	
		pOut ->PrintMessage( " Please draw some filled shapes then come to enjoy playing :) " ); 
		return ;
	}
	
	// case of playing 
	choosen = fig ->GetColour();
	pOut ->PrintMessage ( " select all " + GetColor( choosen ) + " shapes to win :D " ); // telling the user which colour to play with

	total = pManager -> GetCount (  PLAY_CLR , fig ) ; // calculating the total shapes with the playing colour

	while ( correct < total )
{	
	ReadActionParameters(); // getting the selected shape by the user

	if ( ! test ) // if false the user takes another action so ending this action
	{	return;   }
	
	if ( Played != NULL) // testing if the user selected a figure or not
	{
		if ( Played ->GetColour() == choosen && Played ->Getstring() !=  " Line " && Played ->IsFilled() ) //checking if the color is the same random color or not
	{
			correct ++ ;  //No correct increases
			pOut ->PrintMessage (" Correct One :D ! : correct = " +to_string(correct)+ " wrong = " +to_string(wrong) ); //printing correct and the total correct & wrong
		
	}
	else
	{	if ( ( Played ->Getstring() == " Line " || Played ->GetColour() != choosen ) ) // if the user select a wrong figure 
		{
			wrong ++; //No wrong increases
			pOut ->PrintMessage ( "Wrong One :( : correct = " +to_string(correct)+ " wrong = " +to_string(wrong) ); //printing wrong and the total correct & wrong
		  }
	}

	 Played ->setVisiable( false );  // hiding the selected figure 
	pManager ->UpdateInterface(); // redrawing the figlist without the selected figure

	} // if not selected a figure no thing will happend
}
	// after finishing the game

	pManager ->ResetVisibility();  // Redrawing all the hidden figures

	pOut ->PrintMessage ( "Game finished :D :  Total correct = " +to_string(correct)+ "Total wrong = " +to_string(wrong) ); // printing the total correct and wrong 
	
}
PlayColours::~PlayColours()
{
}
