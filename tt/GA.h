#pragma once
#include "timetable.h"
#include <vector>
#include <omp.h>
struct prepod{
	int id;
	int subject1, subject2, subject3;
	map<int,int> subjectids;
	prepod(int id, int sub1, int sub2, int sub3, int actscount){
		subject1 = sub1;
		subject2 = sub2;
		subject3 = sub3;
		subjectids[0] = actscount; 
		subjectids[1] = actscount; 
		subjectids[2] = actscount; 
	}
	int getSubject(int n){
		subjectids[n] = subjectids[n] -1;  
		return subject1;
	}

};
class GA{
public:
	vector<timetable> getNewPopulation();
	vector<timetable> crossingover(vector<timetable> population);
	vector<timetable> mutation(vector<timetable> population);
	vector<timetable> selection(vector<timetable> population);
	GA(void);
	~GA(void);
	void setPopulationSize(int sz);
	void printGrades(vector<timetable> population);
	timetable startGA(int iterations);
private:
	int POPULATION_SIZE;
	timetable getNewTimetable();
	timetable getBest(vector<timetable> population);
	vector<activity> activs;
};

