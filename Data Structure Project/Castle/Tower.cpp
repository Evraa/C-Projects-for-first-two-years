#include "Tower.h"

Tower::Tower()
{
	UnpavedDistance = 30;
	ActiveEnemies = KilledEnemies = 0;
	StopTime=0;
	destroyed = false;
}
void Tower::setFHealth( double h)
{
	if( h>0)
		FHealth =h;
	else
		FHealth = 0;

}

double Tower::getFHealth() const
{
	return FHealth;
}

Tower :: ~Tower ()
{
	ActiveEnemies = KilledEnemies = 0;
}

void Tower::SetStop( int stop)      //set the stop duration of the tower
{
	if( stop > StopTime && stop >0 )
		StopTime = stop;
}
void Tower::UpdateStop()         //update the stop duration of the tower caused by towercontroller enemy to attack it's enemies again
{
	if( StopTime ==0)
		return;
	StopTime--;
}
void Tower::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}
void Tower::setActiveEnemies(int num )
{
	ActiveEnemies =num;
}

double Tower::GetHealth() const
{
	return Health;
}

void Tower:: setFPow (double Pow)
{
	FirePower = Pow > 0 ? Pow : 0;
}

double Tower :: getFpow () const 
{
	return FirePower;
}

void Tower :: setNum (int N)
{
	NumtoShoot = N > 0 ? N : 0;
}

int Tower :: getNum () const 
{ 
	return NumtoShoot;
}

void Tower :: setRegion (REGION R)
{
	TowerRegion = R;
}

REGION Tower :: getReg () const 
{
	return TowerRegion;
}

void Tower::setUnpavedDis(int d)
{
	if( d>= 0&& UnpavedDistance>=d)
		UnpavedDistance = d;
	else
		UnpavedDistance =0;
}

int Tower::getUnpavedDis()const
{
	return UnpavedDistance;
}


void Tower::setDestroyed(bool t)
{
	destroyed = t;
}
bool Tower::getDestroyed()const
{
	return destroyed;
}

void Tower::incrementActiveEnemies()
{
	ActiveEnemies++;
}

void Tower::decrementActiveEnemies()
{
	if( ActiveEnemies !=0)
		ActiveEnemies--;
}

int Tower::getActiveEnemies()const
{
	return ActiveEnemies;
}

void Tower::incrementKilledEnemies()
{
	KilledEnemies++;
}

int Tower::getKilledEnemies()const
{
	return KilledEnemies;
}

void Tower :: Destroy ()         //to free the tower for next game set all data of the towers = 0 
{
	Health = 0;
	NumtoShoot =0;
    FirePower =0;
    UnpavedDistance=30;
    KilledEnemies=0;
    ActiveEnemies=0;
	destroyed=false;
	Active.clear();
	ActiveSheilded.clear();
}

void Tower::Enemies( Enemy* &ptr)                               // add new enemy to each tower
{
	if(!ptr)
		return;
	if( ptr->getSType() =="Shielded")                         //if the enemy was shielded add to shielded list else add to active list 
		ActiveSheilded.add(ptr);
	else
		Active.add(ptr);
	ActiveEnemies++;                                        //increment the number of active enemies
}

void Tower::Move()                                         //the enemies in each region move their speed value if paved
{
	Enemy* ptr;									         //create pointer point to the tower enemy

	bool test = false; 
	int type =1;

	while( type< 3)							          //loop on all the enemy lists first traverse active the shielded list
	{
		getEnemy(ptr,test , type);                  //get the enemy from the tower

		if( ptr )								  //not the end of the list call attack 
			ptr->Move( UnpavedDistance);
		else                                    //at the end of the list change into the other list ( shielded list)
		{
			test = false;
			type++;
		}
	}		
} 

void Tower::AttackEnemy(int Tstep)              //the tower attack its enemies
{
	if( StopTime !=0)						  //if the tower stopped by tower controller don't attack
	{
		UpdateStop();
		return;
	}

	Enemy* ptr;													  //create pointer point to the tower enemy
	bool test = false; 
	int type =2;
	int c = NumtoShoot;										   //get the Number number of enemies the tower can attack
	ActiveSheilded.sort();								      //sort Active-Shielded at each time-step
	
	while( type>0 && c !=0)							        //loop on all the enemy lists first traverse active the shielded list
	{
		getEnemy(ptr,test , type);                         //get the enemy from the tower
		if( ptr )								          //not the end of the list call attack 
		{
			ptr->hitByTower( FirePower , Tstep);        //decrement the enemy's health
			c--;							           //decrement the number of attacked enemies
		}
		else                                         //at the end of the list change into the other list ( Active list)
		{
			test = false;
			type--;
		}
	}
	RemoveKilled();                             //remove killed enemies
}

void Tower::AddNewEnemy( Tower* T)                          //change this function & add function get number of enemies at a certain distance
{
	bool test=false;
	int type =1;                                          //traverse the destroyed tower's enemy lists to set their region and distance
	int dis;
	Enemy * ptr ;
	int count;
	while (type <3)     
	{
		T->getEnemy(ptr,test , type);     
		if( ptr )
		{
			if( ptr->GetDistance() < UnpavedDistance)       //if the enemy will move in unpaved distance set it at the last paved distance
				ptr->SetDistance( UnpavedDistance);
			dis = ptr->GetDistance();
			count = getNoEnemies( dis);                   //get the total number of enemies in the alive tower at the enemy's distance
			while( count >= 15 )                         //if exists 15 enemy ( Max Number of enemies at a certain distance) at the same distance so increment the enemies distance
			{
				ptr ->SetDistance( dis+1);
				dis = ptr->GetDistance();
				count = getNoEnemies(dis);
			}
			ptr ->SetRegion( TowerRegion);          //change the region of the enemies to the new tower's region
			if( type == 1)                         //if the enemy wasn't shielded add it to Active list else add it to shielded list
				Active.add( ptr);  
			else
				ActiveSheilded.add( ptr);
			ActiveEnemies++;                    //increment the Number of Active enemies in the tower
		}
		else
		{
			test =false;
			type++;
		}
	}
	T->Active.clear();                     //free the destroyed tower Active list
	T->ActiveSheilded.clear();	          //free the destroyed tower Shielded list
}


void Tower::AttackTower(MenuItem atm)                            //function attack the tower by its enemies
{
	Enemy* ptr;								                	//create pointer point to the tower enemy
	bool test = false; 
	int type =1;
	while( type< 3)							                  //loop on all the enemy lists first traverse active the shielded list
	{
		getEnemy(ptr,test , type);                           //get the enemy from the tower
		if( ptr )							            	//not the end of the list call attack 
			ptr->Attack(this , atm );
		else                                              //at the end of the list change into the other list ( shielded list)
		{
			test = false;
			type++;
		}
	}
	
}

void Tower::getEnemy( Enemy*& ptr ,bool& test, int type )                        //functione to traverse the Tower Lists
{
	if( type == 1)							                                   //traverse the Active list first
	{
		if(! test )							                                 //if starting to traverse set ref to head of Active list if type=1 
		{
			Active.setRef();
			test = true;
		}
		else                                                              //if not advance the ref and return it
			Active.advanceRef();

		ptr= Active.getRef();
	}
	else                                                              //if type = 2 traverse the shielded enemies list
	{
		if(! test )
		{
			ActiveSheilded.setRef();
			test = true;
		}
		else
			ActiveSheilded.advanceRef();

		ptr= ActiveSheilded.getRef();
	}
}

void Tower::RemoveKilled()                                         //remove killed enemies
{
	Active.setRef();											 //set the head of the Active enemies list
	ActiveSheilded.setRef();									//set the head of the shielded enemies list
	Enemy* Ref =Active.getRef();
	while( Ref)												  //loop on active enemies to remove the killed enemies
	{
		if( Ref ->gethealth() ==0 )
		{
			Active.deleteRef();
			ActiveEnemies--;
			KilledEnemies++;
		}
		else
			Active.advanceRef();
		Ref =Active.getRef();
	}
	Ref = ActiveSheilded.getRef();
	while( Ref)											  //loop on Shielded enemies to remove killed shielded enemies
	{
		if(Ref && Ref ->gethealth() ==0 )
		{
			ActiveSheilded.deleteRef();
			ActiveEnemies--;
			KilledEnemies++;
		}
		else
			ActiveSheilded.advanceRef();
		Ref =ActiveSheilded.getRef();
	}
}

int Tower::getNoEnemies( int dis)						 //return the total Number of enemies at a certain distance
{
	int type=1;											//first traverse active list
	bool test=false;
	Enemy* ptr;
	int count =0;
	while( type<3)    
	{
		getEnemy(ptr, test , type);
		if( ptr)								  //if there is enemy at this distance increment the number of enemies at this distance
		{
			if( ptr ->GetDistance() == dis)
				count++;
		}
		else
		{
			test =false;
			type++;							 //to traverse the shielded list
		}
	}
	return count;						  //return the total number of the enemies
}