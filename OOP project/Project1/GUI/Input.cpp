#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(int x , int y) const
{	
	
	if ( x == 0 && y == 0 )
	{	pWind->WaitMouseClick(x, y); }	//Get the coordinates of the user click

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
				case ITM_LINE: return DRAW_LINE;
				case ITM_RECT: return DRAW_RECT;
				case ITM_TRAG: return DRAW_TRI;
				case ITM_CIRC: return DRAW_CIRC;
				case ITM_CLRBRUSH:return CHNG_DRAW_CLR;
				case ITM_CLRBUCKET:return CHNG_FILL_CLR;
				case ITM_BLACK :return CHNG_CLR_BLACK;
				case ITM_BLUE : return CHNG_CLR_BLUE ;
				case ITM_RED : return CHNG_CLR_RED ;
				case ITM_GREEN :return CHNG_CLR_GREEN ;
				case ITM_WHITE: return CHNG_CLR_WHITE ;
				case ITM_DELETE:return DEL;
				case ITM_SAVE: return SAVE;
				case ITM_LOAD: return LOAD;   //		case ITM_MOVE:return MOVE;
				case ITM_COPY: return COPY;
				case ITM_SELECT: return SELECT;
				case ITM_CUT: return CUT;
				case ITM_PASTE: return PASTE;
				case ITM_TOPLAY:return TO_PLAY;
				case ITM_EXIT: return EXIT;	
			
				default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_SHAPE: return PLAY_SHAPE;
			case ITM_CLR: return PLAY_CLR;
			case ITM_BOTH: return PLAY_BOTH;
			case ITM_TODRAW: return TO_DRAW;
			case ITM_EXIT_PLAY :return EXIT ;
			default: return EMPTY;
			}
		}
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				return PLAYING_AREA;
			}

			//[3] User clicks on the status bar
			return STATUS;
		}
			


		
		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	


/////////////////////////////////
	
Input::~Input()
{
}
