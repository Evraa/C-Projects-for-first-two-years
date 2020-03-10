#include "Supporter.h"

Supporter ::Supporter( REGION r_region, int s, int typ, int t, int rld, double h, double spd,double pow):Enemy(YELLOW,r_region,s,typ,t,rld,h,pow,spd) // children constructor send the data to the base constructor
{
}

void Supporter::Attack( Tower* tower,MenuItem atm)
{
	if( AttackTime !=0 )            //if the enemy in its reloadTime return
		return;
	Enemy* ptr;									//create pointer point to the tower enemy
	bool test = false; 
	int type =1;
	while( type< 3)							   //loop on all the enemy lists first traverse active then shielded list
	{
		tower ->getEnemy(ptr ,test , type);    //get the enemy from the tower
		if( ptr )								//not the end of the list increase the enemies health by the damage-power of the supporter enemy 
		{
			if( ptr ->getSType() != "Supporter" )
			{
				if( ptr ->gethealth() < ptr ->getFhealth() /2)
					ptr ->sethealth( ptr->gethealth() + FPow );
			}
		}
		else                                   //at the end of the list change into the other list ( shielded list)
		{
			test = false;
			type++;
		}
	}
}

string Supporter::getSType() const
{
	return "Supporter";
}

void Supporter::Move(int Unpaved)       //move function of the enemy
{
	int i=0;
	while ( Distance > Unpaved && i <Speed )  //decrement the distance of the enemy by the speed value if paved 
	{
		DecrementDist();
		i++;
	}
}