#pragma once
#include <vector>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include "types.h"
using namespace std;

class timetable
{
public:
	timetable(void);
	~timetable(void);
	void addAuditory(int audtype);
	bool addActivity(int teacher, int subject, int group, int audtype);
	void printTimetable();
	bool shuffle();
private:
	vector<auditory*> auditories;
};

