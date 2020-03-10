#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"

#include "Tower.h"

class Castle
{
	Tower Towers[NoOfRegions];			// array of towers for all the regions
	
public:

	Castle();												 //default constructor 
	void SetTowersHealth(double h);
	double getCastleHealth() const;							 // return the total health of all the towers
	void setTowerRegion( );									//set the region of each tower
	void setTowerPower (double F);						    //set the fire-power of each tower
	void setTowerNum (int N);
	void initializeTowers(double h, double F, int N);
	Tower* getTower(int);
	void addToTower(Enemy *ptr);                      // add enemy to each tower
	void AttackofTowers(int Tstep);                  //each tower in the castle attack its enemies' region 
	void AttackCastle(MenuItem);                    //the enemies attack the castle
	bool ChangeRegion(int );                       //shift the enemies of the destroyed tower to the next alive tower
	void MoveEnemies();                           // to move all the enemies of all regions
	void Replay();                               //to restart the game
};

