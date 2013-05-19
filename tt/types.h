#include <stdio.h>
#include <vector>
#include <stdlib.h>
using namespace std;
#define DAY_LENGHT = 7;
#define WEEK_LENGHT = 6;
struct point {
	int x,y;
};
struct activity{
	int teacher;
	int subject;
	int group;
	int audtype;
	bool used;
	int id;
	activity(){
		teacher = 0;
		subject = 0;
		group = 0;
		audtype = 0;
		id = 0;
		used = false; 
	}
	activity & operator= (activity &act){
		teacher = act.teacher;
		subject = act.subject;
		group = act.group;
		audtype = act.audtype;
		used = act.used;
		id = act.id;
		return *this;
	}
	void reset(){
		teacher = 0;
		subject = 0;
		group = 0;
		audtype = 0;
		used = false;
		id = 0;
	}
};
struct auditory{
	int id;
	int audtype;
	static const int Week_Lenght = 6;
	static const int Day_Lenght = 7;
	activity timetable[Week_Lenght][Day_Lenght];
	auditory(){
		id = 0;
		audtype = 0;
	}
	auditory & operator= (auditory aud){
		int i=0,j=0;
		id = aud.id;
		audtype = aud.audtype;
		for(i=0;i<Week_Lenght;i++){
			for(j=0;j<Day_Lenght;j++){
				timetable[i][j] = aud.timetable[i][j];
			}
		}
		return *this;
	}
	vector<point> findFree(){
		int i=0,j=0;
		vector<point> pts;
		for (i=0;i<Week_Lenght;i++){
			for(j=0;j<Day_Lenght;j++){
				if ( timetable[i][j].used == false ){
					point pt;
					pt.x = i;
					pt.y = j;
					pts.push_back(pt);
				}
			}
		}
		return pts;
	}
};