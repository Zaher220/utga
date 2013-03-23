#include "StdAfx.h"
#include "timetable.h"

timetable::timetable(void){
}

timetable::~timetable(void){
}

void timetable::addAuditory( int audtype ){
	auditory* ad = new auditory();
	ad->audtype = audtype;
	auditories.push_back(ad);
}

bool timetable::addActivity( int teacher, int subject, int group, int audtype ){
	int i=0;
	point* free_aud = NULL;
	bool add_status = false;
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i)->audtype == audtype ){
			free_aud = auditories.at(i)->findFree();
			if( free_aud!= NULL ){
				auditories.at(i)->timetable[free_aud->x][free_aud->y].teacher = teacher;
				auditories.at(i)->timetable[free_aud->x][free_aud->y].subject = subject;
				auditories.at(i)->timetable[free_aud->x][free_aud->y].group = group;
				auditories.at(i)->timetable[free_aud->x][free_aud->y].used = true;
				add_status = true;
				break;
			}
			free_aud = NULL;
		}
	}
	delete free_aud;
	return	add_status;
}

bool timetable::shuffle(){
	int i=0,j=0,k=0,z=0;
	int rrow=0,rcoll=0,raud=0;
	vector<int> auds;
	activity tmpact;
	for(z=0;z<3;z++){
		for(k=0;k<auditories.size();k++){
			if( auditories.at(k)->audtype == z ){
				auds.push_back(k);
			}
		}
		for(k=0;k<auds.size();k++){
			for(i=0;i<6;i++){
				for(j=0;j<7;j++){
					if( auditories.at(auds.at(k))->timetable[i][j].used == true && rand()%2==0){
						raud = rand()%auds.size(); //Получаем рандомную аудиторию
						rrow = rand()%6; //Рандомный день недели 
						rcoll =rand()%7; //Рандомное время
						if( auditories.at(auds.at(raud))->timetable[rrow][rcoll].used == false ){ //Аудитория свободна
							auditories.at(auds.at(raud))->timetable[rrow][rcoll] = auditories.at(auds.at(k))->timetable[i][j]; //Перенесем занятие
							auditories.at(auds.at(k))->timetable[i][j].reset(); // Освободим аудиторию
						}else{//Аудитория занята
							tmpact = auditories.at(auds.at(raud))->timetable[rrow][rcoll];
							auditories.at(auds.at(raud))->timetable[rrow][rcoll] = auditories.at(auds.at(k))->timetable[i][j];
							auditories.at(auds.at(k))->timetable[i][j] = tmpact;
							tmpact.reset();
						}
					}
				}
			}
		}
		auds.clear();
	}
	return true;
}

void timetable::printTimetable(){
	int i=0,j=0,k=0;
	for(i=0;i<auditories.size();i++){
		printf("\n Auditory %d type %d \n",i,auditories.at(i)->audtype);
		printf("*********************************************** \n");
		printf("*   *  1  *  2  *  3  *  4  *  5  *  6  *  7  *\n");
		printf("*********************************************** \n");
		for(k=0;k<6;k++){
			printf("* %d * t=%d * t=%d * t=%d * t=%d * t=%d * t=%d * t=%d *\n"
				,i
				,auditories.at(i)->timetable[k][0].teacher
				,auditories.at(i)->timetable[k][1].teacher
				,auditories.at(i)->timetable[k][2].teacher
				,auditories.at(i)->timetable[k][3].teacher
				,auditories.at(i)->timetable[k][4].teacher
				,auditories.at(i)->timetable[k][5].teacher
				,auditories.at(i)->timetable[k][6].teacher
				);
			printf("*   * s=%d * s=%d * s=%d * s=%d * s=%d * s=%d * t=%d *\n"
				,auditories.at(i)->timetable[k][0].subject
				,auditories.at(i)->timetable[k][1].subject
				,auditories.at(i)->timetable[k][2].subject
				,auditories.at(i)->timetable[k][3].subject
				,auditories.at(i)->timetable[k][4].subject
				,auditories.at(i)->timetable[k][5].subject
				,auditories.at(i)->timetable[k][6].subject
				);
			printf("*   * g=%d * g=%d * g=%d * g=%d * g=%d * g=%d * t=%d *\n"
				,auditories.at(i)->timetable[k][0].group
				,auditories.at(i)->timetable[k][1].group
				,auditories.at(i)->timetable[k][2].group
				,auditories.at(i)->timetable[k][3].group
				,auditories.at(i)->timetable[k][4].group
				,auditories.at(i)->timetable[k][5].group
				,auditories.at(i)->timetable[k][6].group
				);
			printf("*********************************************** \n");
		}
		printf("\n");
	}
}
