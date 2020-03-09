#pragma once
#include "Enemy.h"

class Fighter : public Enemy
{


public:

	Fighter(REGION r_region, int s, int typ, int t, int rld, double h,double spd, double pow); // constructor 
	double DamagePower();								   // calc the Damage of the enemy to the tower
	string getSType()const;								  // type of enemy : Fighter
	virtual void Move(int);								 // how the enemy move during the game
	virtual void Attack( Tower*,MenuItem );				//the attack of the fighter to the tower 
};

