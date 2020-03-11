#include "ChngFillColor.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChngFillColor::ChngFillColor(ApplicationManager * pApp):Action(pApp)
{
	
}
void ChngFillColor:: ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	
	pOut ->PrintMessage ("you want to change the filling color please select one ");
	ColorAct = pManager ->GetUserAction();

	pOut->ClearStatusBar();

}
void ChngFillColor:: Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	

	if (pManager->GetSelectedFig() !=0)
	{
		CFigure* fig = pManager ->GetSelectedFig();
		switch (ColorAct)
	{
	
	case CHNG_CLR_RED:
		{
		fig ->ChngFillClr ( RED );
		pOut ->PrintMessage( " you changed the " + fig ->Getstring() + " Fillinging colour into Red " );	
		}
		break;
	case CHNG_CLR_GREEN:
		{
		fig ->ChngFillClr ( GREEN);
		pOut ->PrintMessage( " you changed the " + fig ->Getstring() + " Filling colour into Green " );
		}
		break;
	case CHNG_CLR_BLUE:
		{
		fig ->ChngFillClr ( BLUE );
		pOut ->PrintMessage( " you changed the " + fig ->Getstring() + " Filling colour into Blue " );
		}
		break;
	case CHNG_CLR_BLACK:
		{
		fig ->ChngFillClr ( BLACK );
		pOut ->PrintMessage( " you changed the " + fig ->Getstring() + " Filling colour into Black " );
		}
		break;
	case CHNG_CLR_WHITE:
		{
		fig ->ChngFillClr( WHITE );
		pOut ->PrintMessage( " you changed the " + fig->Getstring() + " Filling colour into White " );
		}
		break;
	
		fig ->SetSelected( false );
		pManager ->SetSelectedFig( NULL );
		
		}
}
	else {
	switch (ColorAct)
	{
	
	case CHNG_CLR_RED:
		{
		pManager->changeState(true);
		pManager ->changeFcolor( RED );
		pOut ->PrintMessage( " you changed the Filling colour into Red " );
		}
		break;
	case CHNG_CLR_GREEN:
		{
		pManager->changeState(true);
		pManager ->changeFcolor( GREEN );
		pOut ->PrintMessage( " you changed the Filling colour into Green " );
		}
		break;
	case CHNG_CLR_BLUE:
		{
		pManager->changeState(true);
		pManager ->changeFcolor( BLUE );
		pOut ->PrintMessage( " you changed the Filling colour into Blue " );
		}
		break;
	case CHNG_CLR_BLACK:
		{
		pManager->changeState(true);
	    pManager ->changeFcolor( BLACK );
		pOut ->PrintMessage( " you changed the Filling colour into Black " );
		}
		break;
	case CHNG_CLR_WHITE:
		{
		pManager->changeState(true);
		pManager ->changeFcolor( WHITE );
		pOut ->PrintMessage( " you changed the Filling colour into White " );
		}
		break;
	}
	}
}