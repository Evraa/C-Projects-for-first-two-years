#pragma once
#include "Enemy.h"

class Shielded : public Enemy
{


	static double c1,c2,c3;  //priority constants

public:

	Shielded(REGION r_region, int s, int typ, int t, int rld, double h,double spd, double pow); // constructor
	virtual void calcPriority ();											 //calculate the priority of the shielded enemies at each time step
	int getPriority ()const;									   		 // get the priority to use it 
	void static setPriorityConst(double, double, double);			    //set the constants value for the priority from the input file
	 double DamagePower();												//calculate the damage the enemy cause to the tower
	string getSType()const;                                            // the type of the enemy "Shielded" 
	virtual void Move(int);                                           //the movement of the enemy
	virtual void Attack( Tower*,MenuItem );                          //the enemy attack the tower in its region
};

