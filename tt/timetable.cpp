#include "StdAfx.h"
#include "timetable.h"

timetable::timetable(void){
	aud_id = 0;
	act_id = 0;
}

timetable::~timetable(void){
}

void timetable::addAuditory( int audtype ){
	auditory ad;
	ad.audtype = audtype;
	ad.id = aud_id;
	aud_id++;
	auditories.push_back(ad);
	types[audtype] = 1;
}

bool timetable::addActivity( int teacher, int subject, int group, int audtype ){
	int i=0;
	point* free_aud = NULL;
	bool add_status = false;
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i).audtype == audtype ){
			free_aud = auditories.at(i).findFree();
			if( free_aud!= NULL ){
				if( checkFreeActivityPlace(free_aud->x,free_aud->y, group,teacher, audtype) == true ){
					auditories.at(i).timetable[free_aud->x][free_aud->y].teacher = teacher;
					auditories.at(i).timetable[free_aud->x][free_aud->y].subject = subject;
					auditories.at(i).timetable[free_aud->x][free_aud->y].group = group;
					auditories.at(i).timetable[free_aud->x][free_aud->y].used = true;
					auditories.at(i).timetable[free_aud->x][free_aud->y].id = act_id;
					act_id++;
					groups[group] = 1;
					teachers[teacher] = 1;
					subjects[subject] = 1;
					add_status = true;
					break;
				}
			}
			free_aud = NULL;
		}
	}
	delete free_aud;
	if ( add_status == true )
		return	add_status;
	else{
		printf("Cant find place for pair\n");
		return false;
	}

}

void timetable::shuffle( int chance )
{
	int i=0,j=0,k=0,z=0;
	int rrow=0,rcoll=0,raud=0;
	vector<int> auds;
	activity tmpact;
	for(z=1;z<4;z++){
		for(k=0;k<auditories.size();k++){
			if( auditories.at(k).audtype == z ){
				auds.push_back(k);
			}
		}
		for(k=0;k<auds.size();k++){
			for(i=0;i<6;i++){
				for(j=0;j<7;j++){
					if( auditories.at(auds.at(k)).timetable[i][j].used == true && rand()%chance==0){
						raud = rand()%auds.size(); //Получаем рандомную аудиторию
						rrow = rand()%6; //Рандомный день недели 
						rcoll =rand()%7; //Рандомное время
						
						if( auditories.at(auds.at(raud)).timetable[rrow][rcoll].used == false ){//Аудитория свободна
							if ( checkFreeActivityPlace(rrow, rcoll, auditories.at(auds.at(k)).timetable[i][j].group,
								auditories.at(auds.at(k)).timetable[i][j].teacher,	auditories.at(auds.at(k)).timetable[i][j].audtype) == true){ //Время не пересекается
								auditories.at(auds.at(raud)).timetable[rrow][rcoll] = auditories.at(auds.at(k)).timetable[i][j]; //Перенесем занятие
								auditories.at(auds.at(k)).timetable[i][j].reset(); // Освободим аудиторию
							}
						}else{//Аудитория занята
							if ( checkFreeActivityPlace(rrow, rcoll, auditories.at(auds.at(k)).timetable[i][j].group,
								auditories.at(auds.at(k)).timetable[i][j].teacher,	auditories.at(auds.at(k)).timetable[i][j].audtype) == true &&
								checkFreeActivityPlace(i, j, auditories.at(auds.at(k)).timetable[rrow][rcoll].group,
								auditories.at(auds.at(k)).timetable[rrow][rcoll].teacher,	auditories.at(auds.at(k)).timetable[rrow][rcoll].audtype) == true){
									tmpact = auditories.at(auds.at(raud)).timetable[rrow][rcoll];
									auditories.at(auds.at(raud)).timetable[rrow][rcoll] = auditories.at(auds.at(k)).timetable[i][j];
									auditories.at(auds.at(k)).timetable[i][j] = tmpact;
									tmpact.reset();
							}
						}
					}
				}
			}
		}
		auds.clear();
	}
}

void timetable::printTimetable(){
	int i=0,j=0,k=0;
	for(i=0;i<auditories.size();i++){
		printf("\n Auditory %d type %d \n",i,auditories.at(i).audtype);
		printf("**************************************************************\n");
		printf("*   *   1   *   2   *   3   *   4   *   5   *   6   *    7   *\n");
		printf("**************************************************************\n");
		for(k=0;k<6;k++){
			printf("* %d * %d-%d-%d-%d * %d-%d-%d-%d * %d-%d-%d-%d * %d-%d-%d-%d * %d-%d-%d-%d * %d-%d-%d-%d * %d-%d-%d-%d *\n"
				,k+1
				,auditories.at(i).timetable[k][0].teacher,auditories.at(i).timetable[k][0].subject,auditories.at(i).timetable[k][0].group,auditories.at(i).timetable[k][0].id
				,auditories.at(i).timetable[k][1].teacher,auditories.at(i).timetable[k][1].subject,auditories.at(i).timetable[k][1].group,auditories.at(i).timetable[k][1].id
				,auditories.at(i).timetable[k][2].teacher,auditories.at(i).timetable[k][2].subject,auditories.at(i).timetable[k][2].group,auditories.at(i).timetable[k][2].id
				,auditories.at(i).timetable[k][3].teacher,auditories.at(i).timetable[k][3].subject,auditories.at(i).timetable[k][3].group,auditories.at(i).timetable[k][3].id
				,auditories.at(i).timetable[k][4].teacher,auditories.at(i).timetable[k][4].subject,auditories.at(i).timetable[k][4].group,auditories.at(i).timetable[k][4].id
				,auditories.at(i).timetable[k][5].teacher,auditories.at(i).timetable[k][5].subject,auditories.at(i).timetable[k][5].group,auditories.at(i).timetable[k][5].id
				,auditories.at(i).timetable[k][6].teacher,auditories.at(i).timetable[k][6].subject,auditories.at(i).timetable[k][6].group,auditories.at(i).timetable[k][6].id
				);
			printf("**************************************************************\n");
		}
		printf("\n");
	}
}

void timetable::mutate(){
	this->shuffle(5);
}

//Разрыв между парами у группы
int timetable::getWindowGradeForGroup( int gnum ){ 
	int i=0,j=0,z=0,penalty=0,k=0;
	int startpair=-1,endpair=-1;
	for(z=0;z<auditories.size();z++){

		for (i=0;i<6;i++){
			startpair = -1;
			endpair = -1;
			for (j=0;j<7;j++){
				if ( auditories.at(z).timetable[i][j].group == gnum ){
					if ( startpair == -1 )
						startpair = j;
					endpair = j;
				}
			}
			if ( endpair!=-1 ){
				if ( endpair != startpair && endpair-startpair > 1 ){
					//printf("start =%d end=%d\n",startpair,endpair);
					for (k=startpair;k<=endpair;k++){
						if ( auditories.at(z).timetable[i][k].group != gnum )
							penalty++;
						;
					}
					;
				}
			}
		}
	}
	return penalty;
}

int timetable::getGrade(){
	map <int,int>::iterator cur;
	int penalty=0;
	for (cur=groups.begin();cur!=groups.end();cur++){
		penalty += getWindowGradeForGroup((*cur).first);
	}
	return penalty;
}

bool timetable::checkFreeActivityPlace( int day,int time, int group, int teacher, int audtype ){
	int i,j,k;
	for(k=0;k<auditories.size();k++){
		if(auditories.at(k).audtype == audtype){
			if( auditories.at(k).timetable[day][time].group == group || auditories.at(k).timetable[day][time].teacher == teacher  ){
				return false;
			}
		}
	}
	return true;
}

timetable timetable::operator*( timetable const tt ){
	int i=0,j=0,k=0;
	vector<activity> acts;
	timetable* restt = new timetable(*this);
	//Собираем словарь занятий
	for (k=0;k<auditories.size();k++){
		for(i=0;i<6;i++){
			for(j=0;j<7;j++){
				if( auditories.at(k).timetable[i][j].used == true ){
					acts.push_back(auditories.at(k).timetable[i][j]);
				}
			}
		}
	}
	for (k=0;k<restt->auditories.size();k++){
		if ( rand()%2 == 0 ){
			restt->auditories[k] = tt.getAuditoryById(restt->auditories[k].id);
		}
	}
	int cntid;
	printf("acts.size=%d  ",acts.size());
	for(k=0;k<acts.size();k++){
		cntid = restt->countId(acts.at(k).id);
		if ( cntid == 0 )
			printf("Fucking shirt  we lost activity\n");
		else
			if( cntid > 1 ){
				printf("Bliat we have %d ids  id=%d\n",cntid,acts.at(k).id);
			}
	}
	return *restt;
}

auditory timetable::getAuditoryById(int id) const{
	int k=0;
	for (k=0;k<auditories.size();k++){
		if ( auditories.at(k).id == id ){
			return auditories.at(k);
		}
	}
}


int timetable::deleteRepeatingActivities(){
	int i,j,k;
	/*map <int,int> auds_id_count;
	for(k=0;k<auditories.size();k++){
		
	}*/
	return 0;
}

int timetable::countId( int id ){
	int i,j,k;
	int sum=0;
	for(k=0;k<auditories.size();k++){
		for(i=0;i<6;i++){
			for(j=0;j<7;j++){
				if ( auditories.at(k).timetable[i][j].id == id )
					sum++;
			}
		}
	}
	return sum;
}
