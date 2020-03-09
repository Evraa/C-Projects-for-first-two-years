#include "Battle.h"


Battle::Battle()    //battle constructor
{
	EnemyCount = 0;       //intialize all data =0
	totalFD=0;
	totalKD=0;
	totalnumberofenemies=0;
}

Castle * Battle::GetCastle()     //return the castle of the game
{
	return &BCastle;
}

void Battle::DrawBattleArea(GUI * pGUI)
{
	pGUI->ClearBattleArea();
	pGUI->DrawCastle();
	for (int i=0; i<4; i++)           
		pGUI->DrawPavedAreas(GetCastle()->getTower(i));
	pGUI->DrawEnemies(BEnemiesForDraw, EnemyCount);
}

void Battle::AddEnemy(Enemy* Ptr)
{
	if (EnemyCount < MaxEnemyCount) 
		BEnemiesForDraw[EnemyCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It only makes the first free pointer in the array
	// points to what is pointed to by the passed pointer Ptr
}

void Battle::Restart()
{
	BCastle.Replay();						  //first free the castle from any previous data
	inActive.clear();					     //free the inActive from any previous data
	EnemyCount =0;
	totalFD=0;
	totalKD=0;
	totalnumberofenemies=0;
}
void Battle::LoadFunc(GUI * pGUI)			// function to load the game from the file
{
	Restart();
	pGUI->ClearStatusBar();        
	string fileName ;
	if (fileName.size() != 0)				// empty string to get the correct name of the file
	{
		fileName.clear();
	}
	pGUI->PrintMessage("Enter the name of the file you want to load from . ");	
	fileName= pGUI->GetString();													 //get the file name from the user
	fileName = "IO/" + fileName + ".txt";											//add the file extention and directory    
	ifstream inputFile(fileName);
	if (!inputFile.is_open())												      // if the user entered a wrong filename
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("Please, Re-enter the file's corret name");
		return;
	}
		double TH, TP, C1, C2, C3;
		int N;
		inputFile >> TH >> N >> TP >> C1 >> C2 >> C3;							 //read castle info & priority constants
		BCastle.initializeTowers(TH, TP, N);									// initialize the tower from the file info
		Shielded::setPriorityConst(C1, C2, C3);								   // set the priority constants

		while (true)														 // reading the info of the enemies
		{
			int S, TYP, T, RLD;
			char R;
			double H, POW,spd;
			inputFile >> S;

			if (S == -1)                                                 //at the end of the file
			{
				inputFile.close();
				break;
			}
			inputFile >> TYP >> T >> H >> POW >> RLD >> R>> spd;      //read enemy info  
			Enemy* e;

			switch (TYP)											// creating enemies by their types 
			{
			case 0:
				e = new Paver((REGION)R, S, TYP, T, RLD, H, spd, POW);
				break;
			case 1:
				e = new Fighter((REGION)R, S, TYP, T, RLD, H,spd, POW);
				break;
			case 2:
				e = new Shielded((REGION)R, S, TYP, T, RLD, H, spd, POW);
				break;
		   case 3:
			   e= new TowerController((REGION)R, S, TYP, T, RLD, H,spd, POW);
				break;
			case 4:
				e= new Supporter((REGION)R, S, TYP, T, RLD, H,spd, POW);
				break;
			}

			inActive.push(e);									     // add enemy obj to inactive queue
		}
		totalnumberofenemies = inActive.getCount();
}

void Battle::ExecuteAction(MenuItem icon,GUI* pGUI)				  // execute action to take the action from the user
{
	if( icon == MENU_LOAD)                        
		LoadFunc(pGUI);
	else
	{
		if( icon != MENU_EXIT)                               //start the game with the choosen mode
			Simulate( icon , pGUI);
	}
}

void Battle ::Simulate( MenuItem icon,GUI* pGUI)
{
	if( inActive.isEmpty())																	 //if the user play a game without uploading file
	{
		pGUI->PrintMessage(" please insert the file of the game first ");
		return;
	}
	openoutputfile();																		//in every game we prepare the saving file, in the beggining.
	
	int timeStep =1;

	while ( BCastle.getCastleHealth() !=0 && (EnemyCount+inActive.getCount()) != 0 )	  // loop till the castle destroyed or all enemies are killed
	{ 
		if( !inActive .isEmpty() )
		{
			while (inActive.front() && inActive.front()->getArrTime() == timeStep)     //move from inactive to active
			{
				Enemy* temp = inActive.pop();										 //get the enemy from inActive to Active lists
				AddEnemy(temp);														//add the enemy to the drawing area
				BCastle.addToTower( temp );
			}
		}
		if(icon != MENU_SILENT_MODE)
		{
			pGUI->ClearBattleArea();
			DrawBattleArea(pGUI);
			Printinfo( pGUI,timeStep);
			icon = pGUI ->getUserAction( icon );
			if( icon == MENU_EXIT ) 
			{
				Restart();
				pGUI ->ClearBattleArea();
				pGUI ->ClearStatusBar();
				pGUI ->DrawCastle();
				return;
			}
			if( icon == MENU_LOAD)
			{
				pGUI ->ClearBattleArea();
				pGUI ->ClearStatusBar();
				pGUI ->DrawCastle();
				LoadFunc( pGUI);
				return;
			}
			if( icon == MENU_STEP_BY_STEP)
				Sleep(1000);
		}
	
		BCastle.MoveEnemies();		                                              //Move the enemies 
		SetPriority();
		BCastle.AttackCastle(icon);												// the enemies attack the tower
		BCastle.AttackofTowers(timeStep);									   // all the towers attack their enemies
		RemoveKilledEnemies(icon);											  //remove the killed enemies
		
		UpDateEnemyTime();	                                                //undate the attack-Time for each enemy
		timeStep++;														   //increment time-step
	}
	if( icon != MENU_SILENT_MODE)
		Printinfo(pGUI ,timeStep);
	outputtowers(pGUI);
}

void Battle::SetPriority()
{

	for( int i=0;i<EnemyCount;i++)
	{
		if( BEnemiesForDraw[i] ->getType() == 2)
			BEnemiesForDraw[i] ->calcPriority();
	}
}
void Battle ::UpDateEnemyTime()                          //to update the attack time of the enemies at each time-step
{
	if(EnemyCount+ inActive.getCount()==0)              //there is no enemies
		return;

	for( int i=0;i<EnemyCount;i++)                    //update the attack time
		BEnemiesForDraw[i]->updateAttackTime();

}

void Battle::DeleteFormDraw(int indx)                               // to delete the killed enemies from drawing array
{
	BEnemiesForDraw[indx] = BEnemiesForDraw[EnemyCount-1];
	BEnemiesForDraw[--EnemyCount] = NULL;				          //decreament the total active enemies
}

void Battle::RemoveKilledEnemies(MenuItem icon)                  //remove the killed enemies from the game
{
	SoundEffects sound;
	for ( int i = 0 ; i<EnemyCount;i++)                          //loop on all the enemies
		if( BEnemiesForDraw[i]->gethealth() ==0)                // if the enemy is killed
		{
			if( icon != MENU_SILENT_MODE)
				sound.Killedenemies();
			BEnemiesForDraw[i]->calcFD();                    //calculae the killed enemy's first shot delay, to be a prepared data member to add the enemy on its right place
			Killed.addKilled(BEnemiesForDraw[i]);           //add it to the killed list
			
			totalFD+= BEnemiesForDraw[i]->getFD();         //increment data memebers, needed in output file
			totalKD+= BEnemiesForDraw[i]->getKD();
			
			DeleteFormDraw(i);                           //remove it from drawing list
			i--;
		}
		outputfileEnemies();                           //take the "killed" list, traverse it, and make each enemy save itself
}

void Battle ::Printinfo( GUI* pGUI,int TimeStep)      //printing the info on status bar
{
	Tower* temp;
	int Line =2;
	int width =5;
	pGUI ->ClearStatusBar();
	pGUI->PrintMessage("timeStep = " + to_string( TimeStep),1 );          //print the time-step
	for(int i=0;i<4;i++)                                                 //print each tower's info
	{
		temp=BCastle.getTower(i);
		switch (i)
		{
		case 0:
			pGUI->PrintMessage("Region A" ,Line , width);
			break;
		case 1:
			width = 650;
			pGUI->PrintMessage("Region B" ,Line , width);
			break;
		case 2:
			Line =7;
			width =5;
			pGUI->PrintMessage("Region C" ,Line , width);
			break;
		case 3: 
			width = 650;
			pGUI->PrintMessage("Region D" ,Line , width);
			break;
		}
		pGUI ->PrintMessage( "Tower Health = " + to_string( temp->GetHealth()) , Line+1 , width );
		pGUI ->PrintMessage( " No. Active enemies =" + to_string( temp->getActiveEnemies() ) , Line+2 , width );
		pGUI ->PrintMessage (" No. Killed enemies =" + to_string( temp ->getKilledEnemies() ) , Line+3 , width );
		pGUI ->PrintMessage( "UnPaved Distance = " + to_string ( temp ->getUnpavedDis()) , Line+4 , width);

	}
}

void Battle :: outputfileEnemies()          //save each killed enemies
{
	Killed.setRef();
	Enemy* ptr = Killed.getRef(); 
	while( ptr)
	{
		ptr ->SaveMe();               //save the info of the killed enemy then delete it 
		Killed.deleteRef();
		ptr = Killed.getRef();
	}
}


void Battle :: outputtowers(GUI* pGUI)								 //printing the info of the tower and the game result in the file 
{
	ofstream savehere;
	savehere.open("IO/Saving.txt",ios::app);            
	savehere<<endl<<endl;
	savehere << "T1_Total_Damage       T2_Total_Damage       T3_Total_Damage       T4_Total_Damage"<<endl;
	int arr[4];
	
		
	for (int i=0; i<4;i++)										//loop on the towers to get the health of each one
	{
		savehere<< "      " << (BCastle.getTower(i)->getFHealth())-(BCastle.getTower(i)->GetHealth()) << "         ";
		arr[i] =	BCastle.getTower(i)->getUnpavedDis();
	}
	savehere<<endl<<endl;                      
	savehere <<"R1_Unpaved_Dist       R2_Unpaved_Dist       R3_Unpaved_Dist        R4_Unpaved_Dist";
	savehere<<endl;
	SoundEffects sound;
		for (int i=0;i<4;i++)								                             //loop on the towers to get the unpaved dis of each one
		{
			savehere<< "      " << arr[i] << "             ";
		}
		if (EnemyCount == 0 && inActive.isEmpty())			                                                 //in Case of win
		{
			savehere <<endl<<endl<<"THE GAME IS WIN"<<endl<<endl;
			savehere<<"Total number of enemies = "<<totalnumberofenemies<<endl<<endl;                      //print total number of the enemies
			savehere<<"Average First-Shot Delay =   "<<totalFD / totalnumberofenemies<<endl<<endl ;       //print the average of FSD
			savehere<<"Average Kill Delay =   "<<totalKD / totalnumberofenemies<<endl<<endl ;            //print the average of KD
			pGUI->Victory();
			sound.VictorySound();
		}
		else                                                                                          //in Case  of lose
		{
			int kill = totalnumberofenemies-EnemyCount -inActive.getCount();
			savehere << endl << endl << "THE GAME IS LOSE" << endl << endl;                                                                 
			savehere <<"Total number of Active enemies = "<<EnemyCount<<endl<<endl;               //print Number of Active alive enemies
			savehere<<"Total number of InActive enemies = " << inActive.getCount() <<endl;       //print Number of inActive enemies
			savehere<<"Average First-Shot Delay =   "<<totalFD /kill<<endl<<endl ;              //print the average of FSD for killed enemies only
			savehere<<"Average Kill Delay =   "<<totalKD /kill<<endl<<endl ;                   //print the average of KD for killed enemies only
			pGUI->Defeat();
			sound.DefeatSound();
		}
		savehere.close();
}


void Battle :: openoutputfile ()
{
	ofstream savehere;
	savehere.open("IO/Saving.txt",ios::out);            
	savehere.clear();
	savehere <<"KTS    S    FD    KD    LT"<<endl<<endl;
	savehere.close();
}

