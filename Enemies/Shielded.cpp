#include "Shielded.h"

Shielded :: Shielded (REGION r_region, int s, int typ, int t, int rld, double h,double spd, double pow) :Enemy(ORANGERED, r_region,s,typ,t,rld,h,pow,spd)  // children constructor send the data to the base constructor
{
	
}

void Shielded::Attack( Tower* tower,MenuItem atm )
{
	if( AttackTime!=0)
		return;
	SoundEffects sound;
	if( atm != MENU_SILENT_MODE)
		sound.ShieldedSound();
	tower->SetHealth( tower->GetHealth() - DamagePower() );     //decrement the health of the enemy by the enemy's damage
}

double Shielded::DamagePower()
{
	if(getAttacktime()==0)    //if the enemy in its attack time set the damage if not damage =0
		DT = (2*FPow)/Distance;
	else
		DT=0;
	return DT;
}

void Shielded :: calcPriority ()  // calculating the priority at each timestep using the equation with constants and Health & firePower
{
	Priority = ((FPow/Distance)*c1)+ (c2 / (( AttackTime) +1)) +(c3 * Health);
	
}

int Shielded :: getPriority ()const  //return the priority
{
	return Priority;
}
 
void Shielded::setPriorityConst(double t1, double t2, double t3)  // set the constants value of the priority from inputFile
{
	c1 = t1;
	c2 = t2;
	c3 = t3;
}
// initializing the constants of the priority
double Shielded::c1 = 1;
double Shielded::c2 = 1;
double Shielded::c3 = 1;

string Shielded::getSType()const  // type of the enemy : Shileded
{
	return "Shielded";
}

void Shielded::Move(int Unpaved)       //the move of the enemy
{
	int i=0;
	while ( Distance > Unpaved && i <Speed ) //decrement the distance of the enemy by the speed value if paved 
	{
		DecrementDist();
		i++;
	}
}