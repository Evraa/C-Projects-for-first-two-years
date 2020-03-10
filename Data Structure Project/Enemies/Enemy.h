#pragma once
#include <fstream>
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\dataStructures\List.h"
#include "..\Castle\Tower.h"
class Tower;
class Enemy // will be abstract class 
{

protected:
	int ID;				//Each enemy has a unique ID (sequence number)
	color Clr;			//Color of the enemy (will be set depending on the enemy type: Paver, ...etc.)
	REGION Region;		//Region of this enemy
	int Distance;		//Horizontal distance between enemy & the tower of its region,  Always positive (ranges from 2 to 60)

	double Health;		//Enemy health

	double Priority;	// priority for the enemy,  it is zero for paver and fighter and have a calculated value fot the shielded one	

	double FirstHealth; //the initial health of the enemy
	double FPow;		// fire power for the enemy
	double Speed;		//No. meters the enemy move each time-step
	int ReloadTime;		// the time the enemy wait til the next attack
	int Typ;			//will be from 0 to 4 
						// define the type of each enemy : paver , fighter , shielded , supporter and towercontroller
	int ArriveTime;    //the time-step the enemy changed from inactive to active state
	int AttackTime;   //Updated each time-step to know if I can shoot or I will wait.



	//////////////
	

	
	double FirstshotTime;   //the first time-step at which the enemy was shot by the tower
	double KTS;			   //the time-step at which the enemy is killed
	double DT;			   //damage to the tower
	double FD;			  //first shot delay
	double KD ;		     //Kill delay
	double LT;		    // Total time an enemy stay active
	////////////////
	

public:
	
	Enemy(color r_c, char r_region,int s,int typ,int t, int rld,double h,double pow, double spd, int d = MaxDistance);  
	Enemy (){} //default to create constructor for children
	virtual ~Enemy();

	color GetColor() const;

	REGION GetRegion() const;
	void SetRegion(REGION);
	
	

	void SetDistance(int d);
	int GetDistance() const;


	void SetFhealth( double );
	double getFhealth() const;
	
	void SetKTS(int k);

	void SetFirstShotTime( int k);
	int getFirstShotTime () const;

	void sethealth (double H);
	double gethealth() const;

	void setPowerFire (double Pow);
	double getFPower () const;

	void setRelTime (int R);
	int getReltime () const;

	void setType (int T);
	int getType() const;


	void setArrivalTime(int AT);
	int getArrTime() const;

	void setSpeed( double );
	double getSpeed() const;

	void setId(int);
	int getID()const;

	bool operator>(Enemy*);

	
	void updateAttackTime();  //count down for each attck time
	int getAttacktime();  //return the attack time of the enemies

	void hitByTower(double,int) ; // to calc the effect of the tower to the enemy aty each time-step
	//////
	void calcFD (); //calculate the first shot delay
	int getFD() const;
	int getKD(); //Calculate  kill delay of the calling enemy
	void getLT() ;//Calculate  total life time of the calling enemy
	void SaveMe () ; //a function that is called by the killed enemy to allow him to save (store) its own data 
					//the func. append the data of the killed enemy upon the stored data.
	//////////////////

	void DecrementDist();
	// Virtual Functions: ----------------
	virtual string getSType()const=0;
	virtual void calcPriority();
	virtual void Move(int) = 0;	      //Active enemies Move in paved distance
	virtual void Attack( Tower* ,MenuItem )=0;  //Active enemies attack the tower in their attack-time
	///////
	

};

