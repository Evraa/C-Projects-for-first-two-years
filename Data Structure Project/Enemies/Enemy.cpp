#include"Enemy.h"
#include"Shielded.h"

Enemy::Enemy(color r_c, char r_region, int s, int typ, int t, int rld, double h, double pow,double spd, int d) //constructor
{
	Clr = r_c;
	SetDistance(d);
	setArrivalTime(t);
	sethealth(h);
	SetFhealth(h);
	setId(s);
	setType(typ);
	setRelTime(rld);
	setPowerFire(pow);
	setSpeed(spd);
	AttackTime =0;
	KD=0;
	FD=0;
	Priority=0;
	KTS=0;
	FirstshotTime=0;
	LT=0;
	switch (r_region)
	{
	case 'A':
		SetRegion ( A_REG);
		break;
	case 'B':
		SetRegion (B_REG);
		break;
	case 'C':
		SetRegion (C_REG);
		break;
	case 'D':
		SetRegion ( D_REG);
		break;

	}
}

void Enemy::SetRegion(REGION r_region)
{
	Region = r_region;
}

Enemy::~Enemy()
{
}

color Enemy::GetColor() const // return the color of the enemy
{
	return Clr;
}

REGION Enemy::GetRegion() const // return the region of the enemy
{
	return Region;
}

void Enemy::DecrementDist() // make the movement of the enemy
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d) // set the distance where the enemy stands
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const // return where is the enemy to the castle
{
	return Distance;
}
///////
void Enemy :: sethealth (double H) //set the health for each enemy
{
	if (H <= 0)
		Health = 0;
	else
		Health = H;
}

double Enemy :: gethealth () const // return the health of the enemy
{
	return Health;
}
void Enemy ::setSpeed( double s)
{
	if(s >0 )
		Speed = s;
	else
		Speed=1;
}
double Enemy::getSpeed() const
{
	return Speed;
}

void Enemy :: setPowerFire (double Pow) // set the enemy's fire power
{
	FPow = Pow > 0 ? Pow:0 ;
}

double Enemy :: getFPower() const  // return the enemy's fire power
{
	
	return FPow;
}

void Enemy :: setRelTime (int R)  // set the reload time for the enemy
{
	if (R < 0)
	{
		ReloadTime = 0;
		return;
	} //MAX Reload Time

	ReloadTime = R ;
}

int Enemy :: getReltime () const // return the reload time for the enemy
{
	return ReloadTime;
}

void Enemy :: setType (int T)  // set the type of the enemy     // 0 -> paver
{																// 1 -> fighter
	if (T > 4 || T < 0)											// 2 -> Shi
	{                                                           // 3 -> TowerController
		Typ = 0;                                                //4 ->Supporter
		return;
	}
	Typ = T;
}

int Enemy :: getType() const  // return the type of the enemy
{
	return Typ;
}

void Enemy :: setArrivalTime (int AT) //set the arrival time for the enemy
{
	ArriveTime = AT > 0? AT : 1;
}

int Enemy :: getArrTime () const //get the arrival time for the enemy
{
	return ArriveTime;
}

void Enemy::setId(int i) //set the ID for the enemy
{
	ID = i;
}

int Enemy::getID()const //get the ID for the enemy
{
	return ID;
}

void Enemy::SetFhealth( double h)
{
	FirstHealth = h;
}

double Enemy::getFhealth() const
{
	return FirstHealth;
}

void Enemy::getLT()  // calculate the lifetime of the enemy
{
	LT = (FD+ KD);
	
}

bool Enemy::operator>( Enemy* ptr) // operator overloading used in sorting the killed enemies & priority
{
	if (Health == 0) // for the killed enemies get the greater FD 
	{
		if (FD > ptr->getFD())
			return true;
		return false;
	}
	if( dynamic_cast<Shielded*>(ptr))  // for the shielded enemies get the greater in priority 
	{
		if (Priority>ptr->Priority)
			return true;
		return false;
	}
	return true;
	
}

void Enemy::updateAttackTime()       //updated each time step
{
	if(AttackTime > 0)                 //count down the reload time to the next attack 
		AttackTime -= 1;
	else 
		AttackTime = ReloadTime;         //start the count with reload-time value the decrement it at each time-step
}

int Enemy::getAttacktime()
{
	return AttackTime;
}

///////////
void Enemy::SetKTS(int k)
 {
	 KTS = k; 
}



void Enemy::SetFirstShotTime( int k)
{
	FirstshotTime=k;
}


void Enemy :: calcFD ()
{
	FD= FirstshotTime - ArriveTime;
}
int Enemy :: getFD () const {return FD;}


int Enemy::getKD()  //calculate the kill delay
{
	KD=KTS-FirstshotTime;
	return KD;
}



void Enemy::hitByTower(double fP,int timeStep)
{

	double k = 1;
	if (Typ == 2)   //shielded
		k = 0.5;
	if (Health == FirstHealth)				//the enemy is shot for the first time
		SetFirstShotTime(timeStep);
	sethealth(Health - (fP / Distance)*k);  //decrement the distance by tower's fire-power
	if (Health <= 0)						// if the enemy is being killed
	{
		Health = 0;
		SetKTS(timeStep);
	}
}
void Enemy::calcPriority()
{
	Priority = 0;
}
void Enemy :: SaveMe ()  
{
	ofstream savehere;
	savehere.open("IO/Saving.txt",ios::app);
	
	getID();
	calcFD();
	getKD();
	getLT();
	savehere << KTS<<"     "<< ID <<"    "<<FD<<"     "<<KD<<"      "<<LT<<endl;
	savehere.close();
}








