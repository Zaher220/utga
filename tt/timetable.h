#pragma once
#include <vector>
#include <stdio.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include "types.h"
#include <omp.h>
using namespace std;

class timetable
{
public:
	void check();
	bool checkPair(int day, int time, int teacher, int group);
	timetable(void);
	~timetable(void);
	bool addActivity(int teacher, int subject, int group, int audtype, int id);
	void printTimetable();
	void shuffle(int chance = 1);
	void mutate();
	int getGrade();
	timetable operator*(timetable const tt);
	bool operator<(timetable tt);
	void statistics();
	void append(activity act);
	int locateActivitiesWithoutAuditory();
private:
	static const int SCORES = 10000;
	static const int AUD_TYPES_COUNT = 4;
	void locateActivities(); 
	void addAuditory(int audtype);
	auditory getAuditoryById(int id) const;
	int deleteRepeatingActivities();
	int countId(int id);
	bool checkCollisions();
	void deleteActivitiesWithEqualIds();
	bool addUnplacedActivity(int teacher, int subject, int group, int audtype, int id);
	vector<activity> activs;
	int getGradeForActivitiesWithoutAuditory();
	bool resetFirstById(int id);
	int getWindowGradeForGroup(int gnum);
	bool checkFreeActivityPlace(int day,int time, int group, int teacher, int audtype, int audnum);
	vector<auditory> auditories;
	int aud_id, act_id;
	vector<activity> activityWithoutAuditory;
	void addActivityWithoutAuditory(int teacher, int subject, int group, int audtype, int id);
	void clearActivitiesWithoutAuditory();
	map <int,int> groups;
};

