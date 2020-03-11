#include "Drawingcolor.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

DrawingColor::DrawingColor(ApplicationManager * pApp):Action(pApp)
{
	
}
void DrawingColor:: ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut ->PrintMessage ("you want to change the drawing color please select one ");
	ColorAct = pManager ->GetUserAction();

	pOut->ClearStatusBar();
	
}
void DrawingColor:: Execute()
{
	Output* pOut = pManager->GetOutput();
	
	ReadActionParameters();



	//before we enter this if func we must make sure if we want to change the color of a selected shape or the main drawing color

	if (pManager->GetSelectedFig() !=0)
	{
		//a pointer of type cfigure that is assigned an instanc of a specified type of shape to change its own drawn color
		CFigure * fig = pManager ->GetSelectedFig();
		switch (ColorAct)
	{
	
	case CHNG_CLR_RED:
		{
			 fig ->ChngDrawClr( RED );
		     pOut ->PrintMessage( " you changed the " + fig ->Getstring() + " Drawing colour into Red " );
             
		}
		break;
	case CHNG_CLR_GREEN:
		{
			fig ->ChngDrawClr( GREEN );
			pOut ->PrintMessage( " you changed the" + fig ->Getstring() + "  Drawing colour into Green " );
			
		}
		break;
	case CHNG_CLR_BLUE:
		{
	       fig ->ChngDrawClr( BLUE );
		   pOut ->PrintMessage( " you changed the " + fig ->Getstring() + " Drawing colour into Blue " );
		   
		}
		break;
	case CHNG_CLR_BLACK:
		{
		   fig ->ChngDrawClr( BLACK );
		   pOut ->PrintMessage( " you changed the " + fig ->Getstring() +" Drawing colour into Black " );
		  
		}
		break;
	case CHNG_CLR_WHITE:
		{
		   fig ->ChngDrawClr( WHITE );
		   pOut ->PrintMessage( " you changed the " +fig ->Getstring() + " Drawing colour into White " );
		
		
		}
		break;
	}

	
	}
	else {
	switch (ColorAct)
	{
	
	case CHNG_CLR_RED:
		{
		pManager ->changeDcolor( RED );
		pOut ->PrintMessage( " you changed the Drawing colour into Red " );
		}
		break;
	case CHNG_CLR_GREEN:
		{
		pManager ->changeDcolor( GREEN );
		pOut ->PrintMessage( " you changed the Drawing colour into Green " );
		}
		break;
	case CHNG_CLR_BLUE:
		{
		pManager ->changeDcolor( BLUE );
		pOut ->PrintMessage( " you changed the Drawing colour into Blue " );
		}
		break;
	case CHNG_CLR_BLACK:
		{
	    pManager ->changeDcolor( BLACK );
		pOut ->PrintMessage( " you changed the Drawing colour into Black " );
		}
		break;
	case CHNG_CLR_WHITE:
		{
		pManager ->changeDcolor( WHITE );
		pOut ->PrintMessage( " you changed the Drawing colour into White " );
		}
		break;
	}
	}
}


