#include "stdafx.h"
#include "timetable.h"
#include "GA.h"
using namespace std;

void main (){
	freopen("output.txt","w",stdout);
#ifdef _OPENMP
	printf("OpenMP is supported!\n");
#endif
	printf("Population grades\n");
	GA ga;
	ga.setPopulationSize(30);
	ga.startGA(5).printTimetable();
	//timetable tt;

	/*int j=0,i=0;
	int teacher, subject,group,audtype;
	timetable tt;
	for(j=1;j<5;j++){
		for(i=0;i<20;i++){
			tt.addAuditory(j);
		}
	}
	for(int i=0;i<4000;i++){
		audtype = rand()%3+1;
		subject = rand()%5+1;
		teacher = rand()%3+1;
		group = rand()%3+1;
		activity act ;
		act.audtype = audtype;
		act.subject = subject;
		act.teacher = teacher;
		act.group = group;
		act.used = true;
		tt.append(act);
	}
	tt.locateActivities();
	//tt.append()*/
	/*int k;
	scanf("%d",&k);*/
}