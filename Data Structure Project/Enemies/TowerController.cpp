#include "TowerController.h"


TowerController ::TowerController( REGION r_region, int s, int typ, int t, int rld, double h, double spd,double pow):Enemy(BLACK,r_region,s,typ,t,rld,h,pow,spd) // children constructor send the data to the base constructor
{
}

void TowerController::Attack( Tower* tower,MenuItem atm)
{

	if( AttackTime != 0)          //if the enemy in the attack time set the stop-time of the tower by its fire power
		return;
	tower->SetStop( FPow );
}

string TowerController::getSType() const
{
	return "TowerController";
}

void TowerController::Move(int Unpaved)
{
	int i=0;
	while ( Distance > Unpaved && i <Speed )            //loop for move till reach unpaved distance or all the speed value
	{
		DecrementDist();
		i++;
	}
}

