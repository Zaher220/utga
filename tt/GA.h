#pragma once
#include "timetable.h"
#include <vector>
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
};

