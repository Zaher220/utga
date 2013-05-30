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
	ga.setPopulationSize(15);
	ga.startGA(4).printTimetable();
	/*int k;
	scanf("%d",&k);*/
}