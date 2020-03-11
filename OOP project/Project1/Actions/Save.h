#pragma once
#include "Action.h"
#include <fstream>

class Save : public Action
{
	ofstream* GameFile;
	static string fullname;
	static int SavedTimes;
public:

	virtual void ReadActionParameters();
	virtual void Execute();
	Save(ApplicationManager*);
	~Save();
}; 

/* 
---private data member , here we created ofstream pointer to object...initialized with null in the constructor
---two static data members, so that the user when press save,,,he enters the file's name only once and every each time he do so
it overwrite the exisiting file
---and overriding the virtual functions
*/