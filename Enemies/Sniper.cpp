#include "Sniper.h"

Sniper ::Sniper( REGION r_region, int s, int typ, int t, int rld, double h, double pow):Enemy(BLACK,r_region,s,typ,t,rld,h,pow) // children constructor send the data to the base constructor
{
	
}

//void Sniper::Attack(List<Enemy>& Active, List<Enemy>& Shielded , double & THealth, int& TUnpavedDis)
//{
//	THealth = THealth - DamagePower();
//}
//
double Sniper::DamagePower()
{
	if( getAttacktime()==0 )
		DT= FPow;
	else
		DT=0;
	return DT;
}

string Sniper::getSType() const
{
	return " Sniper";
}

void Sniper::Move(int Unpaved)
{
	int i=0;
	if( Speed < 0 && Distance > Unpaved)
		DecrementDist();
	while ( Distance > Unpaved && i <Speed ) //decrement the distance of the enemy by the speed value if paved 
	{
		DecrementDist();
		i++;
	}
}