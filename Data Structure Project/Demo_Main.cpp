#include "Battle.h"
#include "GUI\SoundEffects.h"

int main()
{
	Battle* pGameBattle = new Battle;  // create the battle

	GUI * pGUI = new GUI;  // create Gui to get the user action 

	SoundEffects::Background(); 

	MenuItem icon;

	do
	{
		
		pGUI->ClearStatusBar();
		pGUI ->ClearBattleArea();
		pGUI ->DrawCastle();

		pGUI->PrintMessage("Choose an action.");
		icon = pGUI->getUserAction(); // get the user action 
		pGameBattle->ExecuteAction(icon,pGUI);  // excute the user action
	
	} while (icon != MENU_EXIT);  // loop till exit


	
	delete pGUI;  // deleting the gui
	delete pGameBattle;  // delete the battle
	
	return 0;
}