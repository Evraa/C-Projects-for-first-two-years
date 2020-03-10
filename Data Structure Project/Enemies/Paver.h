#pragma once
#include "Enemy.h"

class Paver : public Enemy
{


public:

	Paver(REGION r_region, int s, int typ, int t, int rld, double h, double spd,double pow);  // constructor
	string getSType()const;                             //the type of the enemy : Paver 
	virtual void Move(int);                            //the movement function of the enemy
	virtual void Attack( Tower*,MenuItem);            //the enemy attack the tower
};

