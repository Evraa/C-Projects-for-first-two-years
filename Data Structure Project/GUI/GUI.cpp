#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0);
	pWind->ChangeTitle("The Castle Game");

	DrawMenu();

	ClearStatusBar();
	ClearBattleArea();
	DrawCastle();
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::GetPointClicked(Point &P ,int z) const
{

	if( z== 0)
		pWind ->GetMouseClick(P.x , P.y);
	else
		pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
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
		ClearStatusBar();	//First clear the status bar
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg , int length ,int width) const	//Prints a message on status bar
{
	//ClearStatusBar();	//First clear the status bar
	pWind->SetPen(DARKRED);
	pWind->SetFont(15, BOLD , BY_NAME, "Arial");   
	switch (length) // switch to make a multi line printing
	{
	case 0:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight), msg); 
		break ; 
	case 1:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+11, msg);
		break;
	case 2:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+2*11, msg);
		break;
	case 3:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+3*11, msg);
		break;
	case 4:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+4*11, msg);
		break;
	case 5:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+5*11, msg);
		break;
	case 6:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+6*11, msg);
		break;
	case 7:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+7*11, msg);
		break;
	case 8:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+8*11, msg);
		break;
	case 9:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+9*11, msg);
		break;
	case 10:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+10*11, msg);
		break;
	case 11:
		pWind->DrawString(width, WindHeight - (int) (StatusBarHeight)+11*11, msg);
		break;
	}	
}
//////////////////////////////////////////w////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawMenu() const
{
	//You can draw the menu icons any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in enum MenuItem
	string MenuItemImages[MENU_ITM_COUNT];

	MenuItemImages[MENU_LOAD] = "images\\MenuItems\\images.jpg";
	MenuItemImages[MENU_EXIT] = "images\\MenuItems\\E.jpg";
	MenuItemImages[MENU_STEP_BY_STEP] = "images\\MenuItems\\I.jpg";
	MenuItemImages[MENU_INTERACTIVE] = "images\\MenuItems\\C.jpg";
	MenuItemImages[MENU_SILENT_MODE] = "images\\MenuItems\\S.jpg";
	
	//
	//TODO: Prepare images for each menu item (an icon for each modes) and add it to the list
	//

	// You should add an icon for each mode of operation (silent, step by step, ...etc.)

	//Draw menu item one image at a time
	for(int i=0; i<MENU_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);

	//Draw a line under the menu bar
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, MenuBarHeight, WindWidth, MenuBarHeight);	
}
MenuItem GUI::getUserAction(MenuItem test)
{
	//PrintMessage("Click anywhere .");
	Point p;
	if( test == MENU_STEP_BY_STEP )
		GetPointClicked(p , 0);
	else
		GetPointClicked(p);
	if( p.x ==-1 && p.y ==-1)
		return MENU_STEP_BY_STEP;
	if (p.y < MenuBarHeight)
	{
		switch (p.x / MenuItemWidth)
		{
		case 0:
			return MENU_LOAD;
		case 1:
			return MENU_STEP_BY_STEP;
		case 2:
			return MENU_INTERACTIVE;
		case 3:
			return MENU_SILENT_MODE;
		case 4:
			return MENU_EXIT;
		//default:
			//return MENU_SILENT_MODE;
		}

		
	}
	if (p.y < (MenuBarHeight + BattleAreaHeight))
		return Battles_Area;

	return Status_Bar;
	
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(WHITE, 3);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearBattleArea() const
{
	// Clearing the battle area
	pWind->SetPen(KHAKI, 3);
	pWind->SetBrush(KHAKI);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastle() const
{
	int L = CastleWidth / 2;
	 string M = "images\\MenuItems\\b.jpg";
	//// 1- Drawing the brown square of the castle
	//pWind->SetPen(BROWN);
	//pWind->SetBrush(BROWN);
	//pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);
	//
	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfBattleArea, WindWidth, YHalfBattleArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth/2, YHalfBattleArea - CastleWidth/2, WindWidth/2, YHalfBattleArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfBattleArea, WindWidth/2 + CastleWidth/2, YHalfBattleArea);
	// Drawing image
	 pWind->DrawImage( M,CastleStartX, CastleStartY , CastleWidth , CastleWidth);
	// 4- Drawing the 4 white squares inside the castle (one for each tower)
	pWind->SetPen(WHITE);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(CastleStartX + L/3, CastleStartY + L/3, CastleStartX + 2*L/3, CastleStartY + 2*L/3);
	pWind->DrawRectangle(CastleStartX + L/3, CastleEndY - L/3, CastleStartX + 2*L/3, CastleEndY - 2*L/3);
	pWind->DrawRectangle(CastleEndX - 2*L/3, CastleStartY + L/3, CastleEndX - L/3, CastleStartY + 2*L/3);
	pWind->DrawRectangle(CastleEndX - 2*L/3, CastleEndY - L/3, CastleEndX - L/3, CastleEndY - 2*L/3);
	
	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(BROWN);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + 0.44*L, CastleStartY + 5*L/12, "A");
	pWind->DrawString(CastleStartX + 0.44*L, YHalfBattleArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + 0.44*L, CastleStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + 0.44*L, YHalfBattleArea + 5*L/12, "C");

	// 6- Drawing the 2 vertical brown lines at distance 60
	// that is because some rounding errors may occur if you choose another width and height for the window
	// so we draw 2 vertical lines at distance 60 to mark it
	pWind->SetPen(BROWN);
	pWind->DrawLine(CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, MenuBarHeight,
		CastleStartX - MaxDistance*EnemyWidth - MaxDistance -1, WindHeight-StatusBarHeight);
	pWind->DrawLine(CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, MenuBarHeight,
		CastleEndX + MaxDistance*EnemyWidth + MaxDistance +1, WindHeight-StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawEnemy(const Enemy & E, int YPos) const       // It's a private function
{
	color clr = E.GetColor();
	REGION Region = E.GetRegion();
	int Distance = E.GetDistance();

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX + (Distance-1)*EnemyWidth + Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; //
		x = refX - Distance*EnemyWidth - Distance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the enemy
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of enemies and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
//    size : the size of the array (total no. of enemies)
void GUI::DrawEnemies(Enemy* enemies[], int size) const
{
	//draw enemies at each region 
	for(int region = A_REG; region <= D_REG; region++)
	{
		int CountEnemies = 0;	// count Enemies at the same distance to draw them vertically if they are <= 15 enemy 
		                        // else print number of enemy in the region
		bool draw=true;
		for(int distance = MaxDistance ; distance >= MinDistance ; distance--)
		{
			CountEnemies = 0;

			for(int i = 0 ; i < size ; i++)
			{	
				if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
				{
					CountEnemies++;
				}
			}
			if(CountEnemies > 15)
			{
				draw=false;
				break;
			}
		}
		if(draw)
		{
			for( int distance = MaxDistance ; distance > 1 ; distance-- )
			{
				CountEnemies=0;

				for(int i = 0 ; i < size ; i++)
				{	
					if(enemies[i]->GetDistance() == distance && enemies[i]->GetRegion() == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies + 1);
						CountEnemies++;
					}
				}
			}
		}
		else // print message maximum reached in this region
		{
			ClearStatusBar();
			PrintMessage("Cannot Draw Enemies of region " + to_string(region+1) + 
				"! More than" + to_string(MaxVerticaEnemies) + " enemies are in the same region and distance..");
			Sleep(1000); // because may be more than one region has drawing overflow
		}
	}
}

void GUI::DrawPavedArea (const Tower* T)
{
	color clr = PINK;							//drawing the PavedArea with red color
	REGION Region = T->getReg();
	int Distance ;
	if( T ->getUnpavedDis() == 0)
		Distance = 8 *( T ->getUnpavedDis());
	else
		Distance=8*( T->getUnpavedDis() -1);
	int x1, y1, x2,y2,refX, refY;

	switch (Region)						   	//For each Region draw the pavedArea
	{
		case A_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; 
		
		x1 =40;
		x2 =refX- Distance;

		y1 = YHalfBattleArea - 5;
		y2 = 50;
		break;

		case B_REG:
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea- 1 - EnemyWidth; 

		x1 = 1260;
		x2 =refX + Distance;

		y1 = YHalfBattleArea - 5;
		y2 = 50;

		break;

     	case C_REG:
		
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth;

		x1 = 1260;
		x2 =refX + Distance;
		
		y1 = refY ;
		y2 = WindHeight - StatusBarHeight - 5;

		break;

	    case D_REG:

		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfBattleArea + 2 + EnemyWidth; 
		x1 = 40; 
		x2 =refX- Distance;

		y1 = refY;
		y2 =  WindHeight - StatusBarHeight - 5;
		break;
	}
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->DrawRectangle(x1, y1, x2 , y2);

}
void GUI :: DrawPavedAreas (Tower * theT)
{
	for (int i=0 ; i<4; i++)  //for each region if the tower alive draw the pavedArea of this tower
	{
		if (theT->GetHealth() > 0 ) //if it's still alive, we will draw it's paved area
		{
			DrawPavedArea( theT );
		}

	}

}


void GUI::Defeat()
{
	ClearBattleArea();
	pWind->DrawImage("images\\MenuItems\\defeat1.jpg", WindWidth / 4, WindHeight / 4, WindWidth / 2, WindHeight / 2);
}

void GUI::Victory()
{
	ClearBattleArea();
	pWind->DrawImage("images\\MenuItems\\victory1.jpg", WindWidth / 4, WindHeight / 4, WindWidth / 2, WindHeight / 2);
}