#include "Paver.h"


Paver :: Paver (REGION r_region, int s, int typ, int t, int rld, double h, double spd,double pow) :Enemy(DARKBLUE, r_region,s,typ,t,rld,h,pow,spd) // children constructor send the data to the base constructor
{
}

void Paver::Attack( Tower*tower ,MenuItem atm)        //how the enemy attack the tower
{
	if( AttackTime !=0)           //if the enemy in its reloadTime return
		return;
	int dis = Distance -tower->getUnpavedDis();      //get the distance between the enemy and the last unpaved distance
	if (dis <= FPow)
	{
		tower->setUnpavedDis(Distance - FPow);
		SoundEffects sound;
		if( atm != MENU_SILENT_MODE)
			sound.PavingSound();
	}
	for( int i=0;i<FPow;i++)              //the enemy move its fire-power in its attack-time
		DecrementDist();
	
}

string Paver::getSType()const // type of the enemy is Paver
{
	return "Paver";
}

void Paver::Move(int Unpaved)
{
	if( AttackTime == 0)    //paver's movement in the attack time is its attack 
		return;
	int i=0;
	while ( Distance > Unpaved && i <Speed )          //decrement the enemy's distance if paved area
	{
		DecrementDist();
		i++;
	}
}



