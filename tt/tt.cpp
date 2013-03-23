#include "stdafx.h"
#include "timetable.h"
using namespace std;

void main (){
	int j=0,i=0;
	int teacher, subject,group,audtype;
	timetable* tt = new timetable();
	freopen("output.txt","w",stdout);
	for(i=0;i<10;i++){
		tt->addAuditory(rand()%3);
	}
	for(int i=0;i<30;i++){
		audtype = rand()%3;
		subject = rand()%6;
		teacher = rand()%4;
		group = rand()%4;
		tt->addActivity(teacher,subject,group,audtype);
	}
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
	scanf("%d",&k);
}