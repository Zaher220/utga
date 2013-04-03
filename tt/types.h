#include <stdio.h>
#include <vector>
#include <stdlib.h>
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
	activity timetable[6][7];
	auditory & operator= (auditory aud){
		int i=0,j=0;
		id = aud.id;
		audtype = aud.audtype;
		for(i=0;i<6;i++){
			for(j=0;j<7;j++){
				timetable[i][j] = aud.timetable[i][j];
			}
		}
		return *this;
	}
	point* findFree(){
		int i=0,j=0;
		point *pt = new point();
		for (i=0;i<6;i++){
			for(j=0;j<7;j++){
				if ( timetable[i][j].used == false ){
					pt->x = i;
					pt->y = j;
					return pt;
				}
			}
		}
		return NULL;
	}
	/*void replaceActivities(point fst, point snd){
		activity tmpact;
		tmpact = timetable[snd.x][snd.y];
		timetable[snd.x][snd.y] = timetable[fst.x][fst.y];
		timetable[fst.x][fst.y] = tmpact;
	}*/
};