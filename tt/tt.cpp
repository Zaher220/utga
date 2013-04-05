#include "stdafx.h"
#include "timetable.h"
using namespace std;

void main (){
	int aud_id=0, act_id=0;
	int j=0,i=0;
	int teacher, subject,group,audtype;
	timetable* tt = new timetable();
	freopen("output.txt","w",stdout);
	for(j=1;j<4;j++){
		for(i=0;i<3;i++){
			tt->addAuditory(j);
		}
	}
	for(int i=0;i<80;i++){
		audtype = rand()%3+1;
		subject = rand()%5+1;
		teacher = rand()%3+1;
		group = rand()%3+1;
		if( tt->addActivity(teacher,subject,group,audtype) == false )
			printf("\nwtf\n");
	}
	for(i=0;i<10;i++){
		tt->shuffle();
	}



	timetable* tt2 = new timetable();

	for(j=1;j<4;j++){
		for(i=0;i<3;i++){
			tt2->addAuditory(j);
		}
	}
	for(int i=0;i<80;i++){
		audtype = rand()%3+1;
		subject = rand()%5+1;
		teacher = rand()%3+1;
		group = rand()%3+1;
		if( tt2->addActivity(teacher,subject,group,audtype) == false )
			printf("\nwtf\n");
	}
	for(i=0;i<10;i++){
		tt2->shuffle();
	}


	timetable* tt3 = new timetable();

	*(tt3) = (*(tt))*(*(tt2));
	tt3->printTimetable();	
	int k;
	//scanf("%d",&k);
}