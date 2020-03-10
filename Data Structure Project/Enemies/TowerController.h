#pragma once
#include"Enemy.h"
class TowerController :public Enemy
{
public:
	TowerController(REGION r_region, int s, int typ, int t, int rld, double h, double spd,double pow);
	string getSType()const;              //string type of the enemy "Tower Controller"
	virtual void Move(int);              //the enemy movement
	virtual void Attack( Tower*,MenuItem );      //the enemy attack the tower
};
