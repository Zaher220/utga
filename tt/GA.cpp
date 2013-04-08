#include "StdAfx.h"
#include "GA.h"
#include <algorithm>

using namespace std;
GA::GA(void){
}


GA::~GA(void){
}

vector<timetable> GA::crossingover( vector<timetable> population ){
	int i=0,j=0;
	vector<timetable> tts;
	for(i=0;i<population.size();i++){
		for(j=0;j<population.size();j++){
			if( i!=j ){
				timetable tt;
				tt = population.at(i)*population.at(j);
				tts.push_back(tt);
			}
		}
	}
	return tts;
}

vector<timetable> GA::selection( vector<timetable> population ){
	int size = (int)sqrt((float)population.size())-1;
	sort(population.begin(),population.end());
	int i=0;
	vector<timetable> respop;
	//printf("population.size()=%d size=%d\n",population.size(),size);
	for(i=0;i<size;i++){
		//printf("population.size()-i=%d\n",population.size()-i-1);
		respop.push_back(population.at(population.size()-i-1));
	}
	/*for(i=population.size();i>population.size()/size;i--){
		respop.push_back(population.at(i));
	}*/
	//return respop;
	return respop;
}

vector<timetable> GA::getNewPopulation(){
	vector<timetable> ttpop;
	int i=0;
	for(i=0;i<POPULATION_SIZE;i++){
		ttpop.push_back(getNewTimetable());
	}
	return ttpop;
}

timetable GA::getNewTimetable(){
	int j=0,i=0;
	int teacher, subject,group,audtype;
	timetable tt;
	for(j=1;j<4;j++){
		for(i=0;i<3;i++){
			tt.addAuditory(j);
		}
	}
	for(int i=0;i<80;i++){
		audtype = rand()%3+1;
		subject = rand()%5+1;
		teacher = rand()%3+1;
		group = rand()%3+1;
		if( tt.addActivity(teacher,subject,group,audtype) == false )
			printf("\nwtf\n");
	}
	tt.shuffle();
	return tt;
}

void GA::setPopulationSize( int sz ){
	POPULATION_SIZE = sz;
}

timetable GA::startGA( int iterations ){
	setPopulationSize(5);
	int i=0;
	vector<timetable> pop;
	for(i=0;i<iterations;i++){
		pop = getNewPopulation();
		pop = crossingover(pop);
		pop = mutation(pop);
		pop = selection(pop);
		printGrades(pop);
	}
	return getBest(pop);
}

timetable GA::getBest( vector<timetable> population ){
	int i=0, best_num=0, best=100000000, grade=0;
	for(i=0;i<population.size();i++){
		grade = population.at(i).getGrade();
		if ( best > grade ){
			best = grade;
			best_num = i;
		}
	}
	return population.at(best_num);
}

void GA::printGrades( vector<timetable> population ){
	int i=0, sum=0, grade;
	for(i=0;i<population.size();i++){
		grade = population.at(i).getGrade();
		sum += grade;
		printf(" %d",grade);
	}
	printf(" summ = %d \n",sum);
}

vector<timetable> GA::mutation( vector<timetable> population ){
	int i=0;
	for(i=0;i<population.size();i++){
		population.at(i).mutate();
	}
	return population;
}
