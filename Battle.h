#pragma once
#include"dataStructures\Queue.cpp"
#include"Enemies\Fighter.h"
#include"Enemies\Paver.h"
#include"Enemies\Shielded.h"
#include"Enemies\Supporter.h"
#include"Enemies\TowerController.h"
#include "Castle\Castle.h"

class Battle
{
private:
	Castle BCastle;
	int EnemyCount;	                                      //the actual number of enemies in the game
	Enemy * BEnemiesForDraw[MaxEnemyCount];              // This Array of Pointers is used for drawing elements in the GUI
													    // No matter what list type you are using to hold enemies, 
													   // you must pass the enemies to the GUI function as an array of enemy pointers. 
													  // At every time step, you should update those pointers 
													 // to point to the current active enemies 
													// then pass the pointers list to the GUI function

	int totalnumberofenemies;
	double totalFD;
	double totalKD;
	List <Enemy> Killed;						//List for the killed enemies to get their information						  
	Queue <Enemy> inActive;					   //the inactive enemies
	//////////////////////////////////
	
public:
	
	Battle();
	void ExecuteAction(MenuItem,GUI*);                      //excute user action 
	void Simulate ( MenuItem , GUI*);                      // simulate the game
	void AddEnemy(Enemy* Ptr);                            //to add enemy to the battle ( drawing area )
	void DrawBattleArea(GUI * pGUI);                     //drawing the enemies 
	Castle * GetCastle();
	void UpDateEnemyTime();                            // update the attack time of the active enemies
	void DeleteFormDraw(int indx);                    //removing the killed enemies from the drawing array 
	void RemoveKilledEnemies(MenuItem);              //remove the killed enemies from the drawing array	
	void Printinfo(GUI* pGUI,int TimeStep);         //to print the info of each region in step-by-step mode and interActive mode
	void LoadFunc(GUI *pGUI);                      //to load the input file of the game
	void outputfileEnemies ();					  // to print the info of the killed enemies during the battle
	void outputtowers (GUI*);					 //to print the info of the towers at the end of the battle
	void SetPriority();						    // to change the priority of shielded enemies at each time step
	void openoutputfile();
	void Restart();                           //to Re-play another game
};

