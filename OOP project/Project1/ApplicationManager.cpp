#include "ApplicationManager.h"
#include "Actions\SelectAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\CutAction.h"
#include "Actions\CopyAction.h"
#include "Actions\PasteAction.h"
#include "Actions\PlayShapes.h"
#include "Actions\PlayColours.h"
#include "Actions\PlayBoth.h"
#include "Actions\ToPlay.h"
#include "Actions\ToDraw.h"
#include "Actions\ChngFillColor.h"
#include "Actions\Drawingcolor.h"
#include "Actions\LoadAct.h"
#include "Actions\Save.h"
#include"Actions\ExitAction.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FILL = false;
	FigCount = 0;
	Clipboard = NULL;
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
	SelectedFig = NULL ;

}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			pAct = new AddLineAction (this);
			break;

		case DRAW_CIRC :
			pAct = new AddCircAction (this);
			break;

			case CHNG_DRAW_CLR :
			
			pAct =new DrawingColor(this);
			break;

		case CHNG_FILL_CLR:
			
			pAct = new ChngFillColor(this);
			break;

			case CHNG_CLR_RED:
			pOut ->PrintMessage ( "please choose you want to change drawing or filling color ");
			break;

		case CHNG_CLR_GREEN:
			pOut ->PrintMessage ( "please choose you want to change drawing or filling color ");
			break;

		case CHNG_CLR_BLUE:
			pOut ->PrintMessage ( "please choose you want to change drawing or filling color ");
			break;

		case CHNG_CLR_BLACK:
			pOut ->PrintMessage ( "please choose you want to change drawing or filling color ");
			break;

		case CHNG_CLR_WHITE:
			pOut ->PrintMessage ( "please choose you want to change drawing or filling color ");
			break;

		case SELECT :
			pAct = new SelectAction (this);
			break ;

		case DRAW_TRI :
			pAct = new AddTrigAction (this);
			break ;

		case DEL :
			pAct = new DeleteAction (this);
			break ;

		case CUT :
			pAct = new CutAction(this);
			break;

		case COPY:
			pAct = new CopyAction(this);
			break;

		case PASTE:
			pAct = new PasteAction(this);
			break;
			
		case TO_PLAY :

			pAct = new ToPlay ( this ); 
			break;
		
		case PLAY_SHAPE :

			pAct = new PlayShapes( this );
	 	    break;
		
		case PLAY_CLR :

			pAct = new PlayColours ( this );
			break;
	
		case PLAY_BOTH :

			pAct = new PlayBoth ( this );
			 break;
		
		case TO_DRAW :
			
			pAct = new ToDraw ( this );
			break;
		       
      
		case SAVE:
			pAct = new Save (this);
			break;
			
		case LOAD:
			pAct = new LoadAct (this);
			break;
		case EXIT:
			///create ExitAction here
			pAct = new ExitAction(this);
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
	{
		FigList[FigCount++] = pFig;	
		FigList[FigCount-1]->SetID(FigCount);
	}
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	CFigure* Temp = NULL ;
	for(int i=FigCount-1; i>=0 && Temp==NULL; i--)
	{	if ( FigList[i] ->Isavilable() )
		{	Temp = FigList [i]->SelectFigure (x,y); }
	}
	return Temp ;
	
}
void ApplicationManager:: SetSelectedFig (CFigure* s)
{
	SelectedFig = s ;
}
CFigure * ApplicationManager:: GetSelectedFig ()const
{
	return SelectedFig;
}
void ApplicationManager::SetClipBoard(CFigure *c)
{
	if (Clipboard==NULL)
	delete Clipboard;
	Clipboard = c;
}
CFigure* ApplicationManager:: GetClipboard ()const
{
	return Clipboard ;
}
void ApplicationManager::ShiftSelected()
{
	int i=(SelectedFig ->GetID());
	for (i;i<FigCount;i++)
	{
		CFigure * Temp;				// the loop starts with i=the id of selected fig
		Temp = FigList[i-1];		//it switckes each two consequent pointers and resets ids
		FigList[i-1] = FigList[i];  //until the selected fig is at the end at of figlist then reduces fig count by 1
		FigList[i] = Temp;
		FigList[i-1] ->SetID(i);
		FigList[i] ->SetID(i+1);
	}
	FigCount -- ;
}

// for PlayMode 

void ApplicationManager :: ResetVisibility()
{
	for ( int i=0; i < FigCount ; i++ )
		FigList[i] ->setVisiable ( true );
}

bool ApplicationManager ::Isfilled () 
{
	for (int start = 0 ; start < FigCount ; start++ )
		 { 
			 if ( FigList[start] ->IsFilled() )
				return true;
	        }
	return false;
	}
CFigure* ApplicationManager :: Random ( ActionType ACT)
{ 
	if ( ACT == PLAY_SHAPE )
   {	
	   if ( FigCount > 0 )
	 { 
	int	Rchoice = rand () % FigCount ;

	return FigList[Rchoice]; }
	   else 
		   return NULL;

	}

	if ( Isfilled() )
	{
		int Rchoice =  rand() % FigCount ;
	
		
		while ( true )
		{	if ( FigList [ Rchoice ] ->IsFilled() && FigList[ Rchoice ] ->Getstring() != " Line " )
				return FigList [ Rchoice ] ;
		else 
				Rchoice = rand() % FigCount ;
		}
	
} 
	return NULL; 
	
}
int ApplicationManager :: GetCount(  ActionType ACT , CFigure* fig )
{
	int Count =0;  
	if ( ACT == PLAY_CLR)
	{
		for ( int i = 0; i < FigCount ; i++ )
		{
			if ( FigList [i] ->IsFilled() )
			{
				if ( FigList[i] ->GetColour() == fig->GetColour() )
					{	Count ++;  }  
			}
		}
		return Count; 
	}
	if ( ACT == PLAY_BOTH )
  {
	  for (int i = 0; i < FigCount ; i ++ ) 
	  { 
		  if ( FigList[i] ->IsFilled() )
		  {
			   if ( (FigList[i] ->GetColour() == fig ->GetColour()  )&&( FigList[i] ->Getstring() == fig ->Getstring()) )
					{  Count ++;  }  
		  }
	 }
	  return Count; 
  }
	if ( ACT == PLAY_SHAPE )
	{
    	for ( int i = 0 ; i < FigCount ; i++ )
		{	
			if ( FigList [i] ->Getstring() == fig ->Getstring() )
				  {	Count++ ;  }
		}
		return Count ;    
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Save and Load Functions Implemintation
int ApplicationManager::getFigCount()
{
	//in order to know , how many figures do we have to save it
	return FigCount;
}
void ApplicationManager :: setfigcount (int n)
{
	//validation for setting the figures count
	if (n>0)
		FigCount=n;
	else
		FigCount=0;
}
void ApplicationManager::Deleting(int figcounter)
{
	for (int i=0; i<figcounter ;i++)
	{
		delete FigList[i];
		FigList[i]=NULL;
	}
}
void ApplicationManager::SaveAll(ofstream& savingINFO)
{
	//saving each figure
	for(int i=0; i<FigCount; i++)
		FigList[i]->Save(savingINFO);
}


void ApplicationManager::LoadThis (ifstream& loadingINFO,CFigure* fig)
{ /*
	--in this function:
	I take a figure, its pointer of type (specified) , so when it calls Load, we already know which figure will call it
	-- it returns the loaded object to be added in the figlist
   */
	AddFigure(fig->Load(loadingINFO));
} 
////////////////////////////////////////

//for colours

void ApplicationManager :: changeDcolor( color Draw )
{
	UI.DrawColor = Draw;
}



void ApplicationManager :: changeState(bool state)
{
	FILL=state;
}
bool ApplicationManager :: getState()
{
	return FILL;
}
void ApplicationManager :: changeFcolor(color Draw)
{
	
	UI.FillColor = Draw;
}

////////////////////////////////////

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut ->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
	{ if ( FigList[i] ->Isavilable() )
	FigList[i]->Draw(pOut);	}	//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
void ApplicationManager:: PrintInfo (CFigure* f) const 
{
	f ->PrintInfo(pOut);
}
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	if (Clipboard==NULL)
		delete Clipboard;
}
