#pragma once
#include "Enemy.h"
class Sniper : public Enemy
{

	Sniper(REGION r_region, int s, int typ, int t, int rld, double h, double pow);
	virtual double DamagePower();
	string getSType()const;
	virtual void Move(int);
	//virtual void Attack(List<Enemy>&, List<Enemy>& , double & , int&);
	//virtual void Attack( Tower* );
};