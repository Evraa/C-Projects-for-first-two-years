#include "Castle.h"


Castle::Castle()
{
	
}
void Castle::Replay()
{
	for( int i=0;i<4;i++)
	{
		if( Towers[i].GetHealth() !=0)
			Towers[i].Destroy();
	}
}
void Castle::SetTowersHealth(double h)							// set the Tower health for each region
{

	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].SetHealth(h);
		Towers[i].setFHealth(h);
	}
}

double Castle::getCastleHealth() const							// to end the fight if the castle lose the game
{
	return ( Towers[0].GetHealth() + Towers[1].GetHealth() + Towers[2].GetHealth() + Towers[3].GetHealth() );

}

void Castle :: setTowerRegion()									// the the tower for each region
{
		Towers[0].setRegion(A_REG);
		Towers[1].setRegion(B_REG);
		Towers[2].setRegion(C_REG);
		Towers[3].setRegion(D_REG);
}
void Castle :: setTowerPower (double F)							//set the tower power 
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setFPow (F);
	}
}
void Castle :: setTowerNum (int N)								// set the Number of enemies the tower can shoot 
{
	for (int i = 0; i < NoOfRegions; i++)
	{
		Towers[i].setNum (N);
	}
}
void Castle::initializeTowers(double h, double f, int n)		// initializing the info of the tower
{
	setTowerRegion();
	SetTowersHealth(h);
	setTowerPower(f);
	setTowerNum(n);
}
Tower* Castle::getTower(int i)
{
	return &Towers[i];
}

void Castle::AttackofTowers(int Tstep)						 //each tower attack its enemies lists
{
	for( int i=0;i<4;i++)
	{
		if( Towers[i].GetHealth() !=0)					//if the tower still alive
			Towers[i].AttackEnemy(Tstep);			   // attack the enemies in it's region
	}
}

void Castle::addToTower(Enemy *ptr)						 // set the enemy in its tower region 
{
	if( getCastleHealth() == 0 )					   //if the castle all destroyed return;
		return;
	bool test = true;
	while(test)                                      //loop on all region until add the enemy to the region
	{
		                                           //if this tower destroyed move the enemy to the second region 
		                                          //if not add the enemy to the tower in this region
		switch (ptr->GetRegion())
		{
			case 0:
				if( Towers[0].GetHealth() == 0) 
					ptr->SetRegion(Towers[1].getReg());
				else           
				{
					Towers[0].Enemies(ptr);
					test=false;
					break;
				}
			case 1:
				if( Towers[1].GetHealth() == 0)
					ptr->SetRegion(Towers[2].getReg());
				else
				{
					Towers[1].Enemies(ptr);
					test=false;
					break;
				}
			case 2:
				if( Towers[2].GetHealth() == 0)
					ptr->SetRegion(Towers[3].getReg());
				else
				{
					Towers[2].Enemies(ptr);
					test=false;
					break;
				}
			case 3:
				if( Towers[3].GetHealth()==0)
					ptr->SetRegion( Towers[0].getReg());
				else
				{
				Towers[3].Enemies(ptr);
				test=false;
				break;
				}
		}
	}
}

void Castle::AttackCastle(MenuItem atm)                                         //each enemy attack the tower in its region
{
	bool test = true;
	for( int i=0;i<4;i++)                                                      //loop on all the towers
	{
		if( Towers[i].GetHealth() !=0)                                        //if the tower still alive it will be attacked by its enemies
		{
			Towers[i].AttackTower(atm);
			if( Towers[i].GetHealth() ==0)
				test = false;
		}
	}
	if(test )
		return;
	for ( int i=0; i<4;i++)
	{
			if (Towers[i].GetHealth() == 0&&!Towers[i].getDestroyed())     //if the tower destroyed shift its enemies o the next alive tower 
		{
			SoundEffects sound;
			if( atm != MENU_SILENT_MODE)
				sound.TowerFallingSound();
			ChangeRegion(i);
			Towers[i].setDestroyed(true);
		}
	}
}

bool Castle::ChangeRegion(int i)                           // add the enemies from destroyed tower to the next alive tower
{
	if( getCastleHealth() == 0 )                         // if all the castle destroyed return false
		return false;
	Towers[i].setActiveEnemies(0);
	if( i!=3 )                                         //add the destroyed tower enemies to the next alive tower from the next of the tower
	{
		for( int k=i+1;k<4;k++)						 //loop on the next towers in the array 
		{
			if( Towers[k].GetHealth() !=0)			//if the tower still alive add the active eneimes of the destroyed tower to it
			{
				Towers[k].AddNewEnemy( &Towers[i]);
				return true;
			}
		}
	}
	for( int k=0;k<4;k++)						 // if the destroyed tower was the last tower or all its next towers are destroyed too check the previos towers
	{
		if( Towers[k].GetHealth() !=0)
		{
			Towers[k].AddNewEnemy( &Towers[i]);
			return true;
		}
	}
}

void Castle::MoveEnemies()
{
	for( int i=0;i<4;i++)                                  //loop on all the towers
	{
		if( Towers[i].GetHealth() !=0)                    //if the tower still alive it will be attacked by its enemies
			Towers[i].Move();
	}
}
