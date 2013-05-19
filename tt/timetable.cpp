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
	types[audtype] = 1;//?unused
}

bool timetable::addActivity( int teacher, int subject, int group, int audtype ){
	int i=0,k=0;
	vector<point> freeplaces;
/*	bool isActivityAdded = false;
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i).audtype == audtype ){
			freeplaces = auditories.at(i).findFree();
			for(k=0;k<freeplaces.size();k++){
				if( checkFreeActivityPlace(freeplaces.at(k).x, freeplaces.at(k).y, group,teacher, audtype, i) == true ){
				}
			}
		}
	}*/
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i).audtype == audtype ){
			freeplaces = auditories.at(i).findFree();
			for(k=0;k<freeplaces.size();k++){
				if( checkFreeActivityPlace(freeplaces.at(k).x, freeplaces.at(k).y, group,teacher, audtype, i) == true ){
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].teacher = teacher;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].subject = subject;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].group = group;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].used = true;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].id = act_id;
					act_id++;
					groups[group] = 1;
					teachers[teacher] = 1;
					subjects[subject] = 1;
					//printf("x=%d  y=%d \n",pts.at(k).x,pts.at(k).y);
					return true;
				}
			}
			freeplaces.clear();
		}
	}
	activity act;
	act.audtype = audtype;
	act.subject = subject;
	act.teacher = teacher;
	act.group = group;
	activityWithoutAuditory.push_back(act);
	//printf("Cant find place for pair\n");
	return false;
}

bool timetable::addActivity( int teacher, int subject, int group, int audtype, int id ){
	int i=0,k=0;
	vector<point> pts;
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i).audtype == audtype ){
			pts = auditories.at(i).findFree();
			printf("pst.size()=%d\n",pts.size());
			for(k=0;k<pts.size();k++){
				if( checkFreeActivityPlace(pts.at(k).x, pts.at(k).y, group,teacher, audtype, i) == true ){
					auditories.at(i).timetable[pts.at(k).x][pts.at(k).y].teacher = teacher;
					auditories.at(i).timetable[pts.at(k).x][pts.at(k).y].subject = subject;
					auditories.at(i).timetable[pts.at(k).x][pts.at(k).y].group = group;
					auditories.at(i).timetable[pts.at(k).x][pts.at(k).y].used = true;
					auditories.at(i).timetable[pts.at(k).x][pts.at(k).y].id = id;
					groups[group] = 1;
					teachers[teacher] = 1;
					subjects[subject] = 1;
					//printf("x=%d  y=%d \n",pts.at(k).x,pts.at(k).y);
					return true;
				}
			}
			pts.clear();
		}
	}
	activity act;
	act.audtype = audtype;
	act.subject = subject;
	act.teacher = teacher;
	act.group = group;
	act.id = id;
	activityWithoutAuditory.push_back(act);
	//printf("Cant find place for pair\n");
	return false;
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
								auditories.at(auds.at(k)).timetable[i][j].teacher,	auditories.at(auds.at(k)).timetable[i][j].audtype, k) == true){ //Время не пересекается
								auditories.at(auds.at(raud)).timetable[rrow][rcoll] = auditories.at(auds.at(k)).timetable[i][j]; //Перенесем занятие
								auditories.at(auds.at(k)).timetable[i][j].reset(); // Освободим аудиторию
							}
						}else{//Аудитория занята
							if ( checkFreeActivityPlace(rrow, rcoll, auditories.at(auds.at(k)).timetable[i][j].group,
								auditories.at(auds.at(k)).timetable[i][j].teacher,	auditories.at(auds.at(k)).timetable[i][j].audtype, k) == true &&
								checkFreeActivityPlace(i, j, auditories.at(auds.at(k)).timetable[rrow][rcoll].group,
								auditories.at(auds.at(k)).timetable[rrow][rcoll].teacher,	auditories.at(auds.at(k)).timetable[rrow][rcoll].audtype, k) == true){
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
	//printf("mutate\n");
	locateActivitiesWithoutAuditory();
	this->shuffle(2);
	locateActivitiesWithoutAuditory();
	//printf("activityWithoutAuditory=%d\n",activityWithoutAuditory.size());
/*while ( activityWithoutAuditory.size() > 0 ){
		printf("activityWithoutAuditory=%d\n",activityWithoutAuditory.size());
		this->shuffle(2);
		locateActivitiesWithoutAuditory();
	}*/
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
	//penalty += getGradeForActivitiesWithoutAuditory();
	return penalty;
}

bool timetable::checkFreeActivityPlace( int day, int time, int group, int teacher, int audtype, int audnum ){
	int i,j,k;
	for(k=0;k<auditories.size();k++){
		if( k!= audnum && auditories.at(k).audtype == audtype){
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
				if( auditories.at(k).timetable[i][j].used == true && auditories.at(k).timetable[i][j].id != 0){
					acts.push_back(auditories.at(k).timetable[i][j]);
				}
			}
		}
	}
	for (k=0;k<restt->auditories.size();k++){
		if ( rand()%2 == 0 ){
			if ( tt.getAuditoryById(restt->auditories[k].id).audtype != 0 ){
				restt->auditories[k] = tt.getAuditoryById(restt->auditories[k].id);
			}
		}
	}
	int cntid;
	//printf("acts.size=%d  ",acts.size());
	
	for(k=0;k<acts.size();k++){
		cntid = restt->countId(acts.at(k).id);
		if( cntid > 1 ){
			restt->resetFirstById(acts.at(k).id);
			//printf("Bliat we have %d ids  id=%d\n",cntid,acts.at(k).id);
		}
		if ( cntid == 0 ){
			//printf("cnt=%d acts.at(k).id=%d Fucking shirt  we lost activity\n",cntid,acts.at(k).id);
			restt->addActivity(acts.at(i).teacher, acts.at(i).subject, acts.at(i).group, acts.at(i).audtype, acts.at(i).id);
		}			
	}
	checkCollisions();

	return *restt;
}

auditory timetable::getAuditoryById(int id) const{
	int k=0;
	for (k=0;k<auditories.size();k++){
		if ( auditories.at(k).id == id ){
			return auditories.at(k);
		}
	}
	auditory aud;
	return aud;
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

bool timetable::checkCollisions(){
	int i,j,k;
	activity act;
	for(k=0;k<auditories.size();k++){
		for(i=0;i<6;i++){
			for(j=0;j<7;j++){
				if ( auditories.at(k).timetable[i][j].used == true ){
					if ( checkFreeActivityPlace(i,j,auditories.at(k).timetable[i][j].group,auditories.at(k).timetable[i][j].teacher,auditories.at(k).timetable[i][j].audtype, k) == false  ){
						//printf("collisons detected\n");
						act = auditories.at(k).timetable[i][j];
						auditories.at(k).timetable[i][j].reset();
						if ( !addActivity(act.teacher,act.subject,act.group,act.audtype) ){
							//addActivityWithoutAuditory(act.teacher,act.subject,act.group,act.audtype,act.id);
							printf("Cant solve collision\n");
						}
						//nado ispravliat kolliziu
					}
				}
			}
		}
	}
	return true;
}

bool timetable::resetFirstById( int id ){
	int i,j,k;
	for(k=0;k<auditories.size();k++){
		for(i=0;i<6;i++){
			for(j=0;j<7;j++){
				if ( auditories.at(k).timetable[i][j].id == id ){
					auditories.at(k).timetable[i][j].reset();
					return true;
				}
			}
		}
	}
}

bool timetable::operator<( timetable tt ){
	if ( getGrade() > tt.getGrade() )
		return true;
	else
		return false;

}

void timetable::addActivityWithoutAuditory( int teacher, int subject, int group, int audtype, int id ){
	activity act;
	act.audtype = audtype;
	act.group = group;
	act.id = id;
	act.subject = subject;
	act.teacher = teacher;
	activityWithoutAuditory.push_back(act);
}

int timetable::getGradeForActivitiesWithoutAuditory(){
	return activityWithoutAuditory.size();
}

int timetable::locateActivitiesWithoutAuditory(){
	vector<activity>::iterator i;
	for(i=activityWithoutAuditory.begin();i!=activityWithoutAuditory.end();i++){
		if ( !addUnplacedActivity(i->teacher, i->subject, i->group, i->audtype,i->id)	){
			//printf("CantlocateActivitiesWithoutAuditory\n");
		}else{
			///printf("Activity is located ");
			//printf("before %d",activityWithoutAuditory.size());
			activityWithoutAuditory.erase(i);
			///printf("after %d \n",activityWithoutAuditory.size());
		}
	}
	return activityWithoutAuditory.size();
}

void timetable::statistics(){
	printf("activityes without auditory = %d\n",activityWithoutAuditory.size());
	/*for(k=0;k<auditories.size();k++){
		for(i=0;i<6;i++){
			for(j=0;j<7;j++){
				if ( auditories.at(k).timetable[i][j].used == true ){
					
				}
			}
		}
	}*/
}

void timetable::append( activity act ){
	activs.push_back(act);
	printf("size=%d",activs.size());
}

void timetable::locateActivities(){
	map<int,int> counttypedacts;
	map<int,int>::iterator it;
	for(int i=0;i<activs.size();i++)
		if ( counttypedacts.count(activs.at(i).audtype) > 0 )
			counttypedacts[activs.at(i).audtype] = 1;
		else
			counttypedacts[activs.at(i).audtype]++;
	for(it = counttypedacts.begin();it!=counttypedacts.end();it++){
		printf("%d \n",it->second);
	}
}

bool timetable::addUnplacedActivity( int teacher, int subject, int group, int audtype, int id )
{
	int i=0,k=0;
	vector<point> freeplaces;
/*	bool isActivityAdded = false;
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i).audtype == audtype ){
			freeplaces = auditories.at(i).findFree();
			for(k=0;k<freeplaces.size();k++){
				if( checkFreeActivityPlace(freeplaces.at(k).x, freeplaces.at(k).y, group,teacher, audtype, i) == true ){
				}
			}
		}
	}*/
	for(i=0;i<auditories.size();i++){
		if ( auditories.at(i).audtype == audtype ){
			freeplaces = auditories.at(i).findFree();
			for(k=0;k<freeplaces.size();k++){
				if( checkFreeActivityPlace(freeplaces.at(k).x, freeplaces.at(k).y, group,teacher, audtype, i) == true ){
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].teacher = teacher;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].subject = subject;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].group = group;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].used = true;
					auditories.at(i).timetable[freeplaces.at(k).x][freeplaces.at(k).y].id = act_id;
					act_id++;
					groups[group] = 1;
					teachers[teacher] = 1;
					subjects[subject] = 1;
					//printf("x=%d  y=%d \n",pts.at(k).x,pts.at(k).y);
					return true;
				}
			}
			freeplaces.clear();
		}
	}
	//printf("Cant find place for pair\n");
	return false;
}
