#pragma once
#include "..\Defs.h"
#include "..\dataStructures\List.cpp"
#include "..\Enemies\Enemy.h"
#include "..\GUI\SoundEffects.h"

class Enemy;
class Tower
{
	double Health;			                      // the health of each tower
	double FHealth;                              //the first health of the tower
	int NumtoShoot;			                    // number of enemies the tower can shoot at each timestep
	double FirePower;						   // the Fire that the tower can damage the enemy by
	REGION TowerRegion;						  // the region for each tower
	int UnpavedDistance;	                 // the tower's unpaved area
	int ActiveEnemies;		                // No. of active enemies fight the tower
	int KilledEnemies;		               // No. of killeded enemies by the tower
	int StopTime;			              // the duration the tower stop to attack its enemies
	bool destroyed;						 //to know the tower still alive or not
	List <Enemy> ActiveSheilded;		//List of shielded enemies
	List <Enemy> Active;			   //List of paver , supporter , sinper and fighter enemies
	SoundEffects* sound;              //pointer to sound effects class to call sound functions
public:
	
	Tower();                                                  // default constructor
	~Tower();                                                //destructor
	 
	void SetHealth(double h);			                    //set the health for the tower
	double GetHealth() const;		                       //return the health of the tower
	
	void setFHealth( double h);                           //set the first health value
	double getFHealth() const;						     //return the first health value

	void setNum (int N);                                // set the number of enemies the tower can shoot
	int getNum () const;                               // return the number of enemies the tower can shoot

	void setFPow (double Pow);                        //set the figher power of the enemy
	double getFpow () const;                         //return the figher power of the nemey

	void setRegion (REGION R);		               //set the region for the tower
	REGION getReg () const;			              //return the region of the tower

	void setUnpavedDis(int);				    // to set the unpaved distance of the tower
	int getUnpavedDis()const;				   // return the unpaved distance of the tower

	void setDestroyed(bool);
	bool getDestroyed()const;

	void incrementActiveEnemies();		   //increase the active enemies number
	void decrementActiveEnemies();		  //decrease the distance between enemy and tower at each time-step
	int getActiveEnemies()const;		 //return the number of active enemies of the tower
	void setActiveEnemies( int ); 
	void incrementKilledEnemies();		// increase the killed enemies for the tower
	int getKilledEnemies()const;
	void Destroy ();				//reset the active & killed enemies =0 

	////////////////////////////////////////////
	int getNoEnemies( int dis);				                  //return the total number of enemies at certain distance
	void Enemies(Enemy *&ptr);				                 //to add active enemy to the tower
	void AttackEnemy(int Tstep);			                //each tower attack the enemies of its region 
	void Move();							               // the movement of the enemies   
	void AttackTower(MenuItem);				              //the attack caused by the enemies to the tower
	void AddNewEnemy ( Tower* );			             // add the enemies from destroyed tower to the alive tower
	void SetStop( int );					            //set the stop-time 
	void UpdateStop();								   // count down to the stop-time to continue the tower attack
	void RemoveKilled();							  //remove the killed enemies at each time-step
	void getEnemy( Enemy*& , bool& , int);			 //function to traverse the two lists of the tower enemies
};

