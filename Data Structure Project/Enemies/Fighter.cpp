#include "Fighter.h"

Fighter :: Fighter ( REGION r_region, int s, int typ, int t, int rld, double h, double spd,double pow):Enemy(DARKOLIVEGREEN,r_region,s,typ,t,rld,h,pow,spd) // children constructor send the data to the base constructor
{
	
}

void Fighter::Attack( Tower* tower ,MenuItem atm)          //how enemy attack the tower in its region
{
	if( AttackTime !=0)                  //if the enemy in its reloadTime return
		return;
	SoundEffects sound;
	if( atm != MENU_SILENT_MODE)
		sound.FighterSound();
	tower->SetHealth( tower->GetHealth() - DamagePower() );   //if in attackTime decrement the tower health by its Damage-power
}

double Fighter::DamagePower()   //return the damage the enemy decrease the tower's health by
{
	DT =FPow/Distance;
	return DT;
}
string Fighter::getSType()const // type of enemy Fighter 
{
	return "Fighter";
}

void Fighter::Move(int Unpaved)
{
	int i=0;
	while ( Distance > Unpaved && i <Speed ) //decrement the distance of the enemy by the speed value if paved 
	{
		DecrementDist();
		i++;
	}
}