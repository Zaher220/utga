#include "StdAfx.h"
#include "GA.h"
#include <algorithm>

using namespace std;
GA::GA(void){
	int j=0,i=0;
	int teacher, subject,group,audtype;
	vector<prepod> pps;
	vector<activity> acts;
	for( int i=0; i<10; i++){
		prepod pp(i,i,i+1,i+2,8);
		pps.push_back(pp);		
	}// Преподы с предметами
	int groupcount=20, paircount = 30;
	int id = 0;
	for( int i=0; i<groupcount;i++){
		for(int k=0;k<pps.size();k++){
			for(int n=0;n<3;n++){
				activity act;
				act.audtype = rand()%3+1;
				act.subject = pps.at(k).getSubject(n);
				act.teacher = pps.at(k).id;
				act.group = i;
				act.id = id ;
				id++;
				activs.push_back(act);
			}
		}
	}
	/*for(int i =0;i<activs.size();i++){
		printf("type=%d grp=%d sbjct=%d tchr=%d id=%d \n",activs.at(i).audtype, activs.at(i).group, activs.at(i).subject, activs.at(i).teacher, activs.at(i).id);
		
	}*/
 	/*map<int,int> grps,sbjs,tchs;
	for(i=0;i<10;i++){
		grps[i] = 30;
	}
	for(i=0;i<10;i++){
		tchs[i] = 30;
	}
	for ( i=0;i<groupcount;i++){
		for(j=0;j<tcount;j++)
	}*/
	/*for(int i=0;i<700;i++){
		activity act;
		act.audtype = rand()%3+1;
		act.subject = rand()%5+1;
		act.teacher = rand()%3+1;
		act.group = rand()%3+1;
		act.id;
		activs.push_back(act);
	}*/
}


GA::~GA(void){
}

vector<timetable> GA::crossingover( vector<timetable> population ){
	int i=0,j=0;
	vector<timetable> tts;
	
	for(i=0;i<population.size();i++){
		//#pragma omp parallel for num_threads(2)
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
	int size = (int)sqrt((float)population.size());
	size+=2;
	sort(population.begin(),population.end());
	int i=0;
	vector<timetable> respop;
	//#pragma omp parallel for num_threads(2)
	for(i=0;i<size;i++){
		respop.push_back(population.at(population.size()-i-1));
	}
	if ( respop.size()>POPULATION_SIZE )
		respop.erase(respop.begin()+POPULATION_SIZE,respop.end());
	return respop;
}

vector<timetable> GA::getNewPopulation(){
	vector<timetable> ttpop;
	int i=0;
	//#pragma omp parallel for num_threads(2)
	//printf("sz=%d\n",POPULATION_SIZE);
	for(i=0;i<POPULATION_SIZE;i++){
		ttpop.push_back(getNewTimetable());
	}
	return ttpop;
}

timetable GA::getNewTimetable(){
	int j=0,i=0;
	int teacher, subject,group,audtype;
	timetable tt;
	for(j=1;j<5;j++){
		for(i=0;i<4;i++){
			tt.addAuditory(j);
		}
	}
	int addingerrorcount=0;
	for(i=0;i<activs.size();i++){
		if( tt.addActivity(activs.at(i).teacher,activs.at(i).subject,activs.at(i).group,activs.at(i).audtype) == false )
			addingerrorcount++;
	}
	//printf("cant add %dd accts\n",addingerrorcount);
	tt.shuffle();
	return tt;
}

void GA::setPopulationSize( int sz ){
	POPULATION_SIZE = sz;
}

timetable GA::startGA( int iterations ){
	int i=0;
	vector<timetable> pop;
	pop = getNewPopulation();
	for(i=0;i<iterations;i++){
		
		pop = crossingover(pop);
		//pop = mutation(pop);
		pop = selection(pop);
		printGrades(pop);
		pop = mutation(pop);
		//printf("pop.size=%d\n",pop.size());
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
		printf(" ;%d",grade);
	}
	printf(" ;%d\n",sum/population.size());
}

vector<timetable> GA::mutation( vector<timetable> population ){
	int i=0;
	for(i=0;i<population.size();i++){
		population.at(i).mutate();
	}
	return population;
}
