#pragma once
#include <vector>
#include <stdio.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include "types.h"
using namespace std;

class timetable
{
public:
	static const int SCORES = 10000;
	timetable(void);
	~timetable(void);
	void addAuditory(int audtype);
	bool addActivity(int teacher, int subject, int group, int audtype);
	void printTimetable();
	void shuffle(int chance = 1);
	void mutate();
	int getGrade();
	timetable operator*(timetable const tt);
	auditory getAuditoryById(int id) const;
	int deleteRepeatingActivities();
	int countId(int id);
private:
	int getWindowGradeForGroup(int gnum);
	bool checkFreeActivityPlace(int day,int time, int group, int teacher, int audtype);
	vector<auditory> auditories;
	int aud_id, act_id;
	map <int,int> types;
	map <int,int> teachers;
	map <int,int> groups;
	map <int,int> subjects;
};

