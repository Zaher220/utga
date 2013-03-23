#include "stdafx.h"
#include "timetable.h"
using namespace std;

void main (){
	int j=0,i=0;
	int teacher, subject,group,audtype;
	timetable* tt = new timetable();
	freopen("output.txt","w",stdout);
	for(j=1;j<4;j++){
		for(i=0;i<2;i++){
			tt->addAuditory(j);
		}
	}
	for(int i=0;i<120;i++){
		audtype = rand()%3+1;
		subject = rand()%5+1;
		teacher = rand()%3+1;
		group = rand()%3+1;
		if( tt->addActivity(teacher,subject,group,audtype) == false )
			printf("\nwtf\n");
	}
	tt->shuffle();
	tt->printTimetable();
	/*vector<activity*> acts;
	vector<auditory*> auds;
	for(int i=0;i<10;i++){
		auditory *ad =new auditory;
		ad->audtype = rand()%3;
		auds.push_back(ad);
	}
	for(int i=0;i<10;i++){
		activity *ac = new activity;
		ac->audtype = rand()%3;
		ac->subject = rand()%6;
		ac->teacher = rand()%4;
		ac->group = rand()%4;
		acts.push_back(ac);
		printActivity(ac);
	}
	for(j=0;j<auds.size();j++){

		auds.at(j)->printNonFree();
		printf("++++++++++");
		//printAuditory(auds.at(j));
	}
	int  atype = 1;
	for(i=0;i<acts.size();i++){
		for(j=0;j<auds.size();j++){
			if( acts.at(i)->audtype == auds.at(j)->audtype ){
				if( auds.at(i)->findFree()>=0 ){
					auds.at(j)->timetable[auds.at(i)->freex][auds.at(i)->freey] = acts.at(j);
					
					acts.at(j)->used = true;
					j = auds.size();
				}
			}
		}
	}
	*/
	int k;
	//scanf("%d",&k);
}