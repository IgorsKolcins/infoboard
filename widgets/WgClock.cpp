#include "WgClock.h"
#include "../CFontStorage.h"

WgClock::WgClock(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode):
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	updateTime = 0.25;
	readFile(SCH);
	setDateTime();
	setSchedule();
	update();
}

void WgClock::readFile(json &aj, char *FileName){
	cout << "--start reading ... " << FileName;
	ifstream i(FileName);
	i >> aj;
	cout << " ... reading end--" << endl;
}

struct WgClock::DATE WgClock::jToDate(double j){
	struct DATE temp;
	int ibuf = j*100;
    temp.d = ibuf/100;
    temp.m = ibuf%100;
    return temp;
}

struct WgClock::TIME WgClock::jToTime(double j){
	struct TIME temp;
	int ibuf = j*100;
    temp.h = ibuf/100;
    temp.m = ibuf%100;
    return temp;
}

int WgClock::timer(int hour1, int min1, int sec1, int hour2 ,int min2, int sec2){
	return (hour1*3600 + min1*60 + sec1) - (hour2 * 3600 + min2 *60 + sec2); 
}

void WgClock::setDateTime(){
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sscanf(asctime(timeinfo), "%[^ ] %[^ ] %d %d:%d:%d %d", WEEK, MOUNTH, &NOW.d, &HOUR, &MIN, &SEC, &YEAR);
	//cout << "HOUR" << HOUR <<endl;
	if ( ! strcmp(MOUNTH, "Jan") ) NOW.m = 1;
	else if ( ! strcmp(MOUNTH, "Feb") ) NOW.m = 2;
	else if ( ! strcmp(MOUNTH, "Mar") ) NOW.m = 3;
	else if ( ! strcmp(MOUNTH, "Apr") ) NOW.m = 4;
	else if ( ! strcmp(MOUNTH, "May") ) NOW.m = 5;
	else if ( ! strcmp(MOUNTH, "June") ) NOW.m = 6;
	else if ( ! strcmp(MOUNTH, "July") ) NOW.m = 7;
	else if ( ! strcmp(MOUNTH, "Aug") ) NOW.m = 8;
	else if ( ! strcmp(MOUNTH, "Sept") ) NOW.m = 9;
	else if ( ! strcmp(MOUNTH, "Oct") ) NOW.m = 10;
	else if ( ! strcmp(MOUNTH, "Nov") ) NOW.m = 11;
	else if ( ! strcmp(MOUNTH, "Dec") ) NOW.m = 12;

}

void WgClock::setSchedule(){
	
	char buf[2]; buf[1]='\0';
	char buff[2]; buff[1]='\0';
	DATE start, finish;
			
	if (SCH["EXCEPTION"]["value"].is_number())	
	{
		if (SCH["EXCEPTION"]["value"] != 0)
		{
			for (int i=0; i < SCH["EXCEPTION"]["value"]; i++)
			{
				buf[0] = 49+i;
				start = jToDate(SCH["EXCEPTION"][buf]["start"]);
				finish = jToDate(SCH["EXCEPTION"][buf]["finish"]);
				if (NOW.d >= start.d && NOW.m >= start.m && 
					NOW.d <= finish.d && NOW.m <= finish.m)
				{
					ParaValue = SCH["EXCEPTION"][buf]["paravalue"];
					for (int j=0; j < ParaValue; j++)
					{
						buff[0] = 49+j;
						if (!SCH["EXCEPTION"][buf][buff]["isdefault"]) pi[j].begin = jToTime(SCH["EXCEPTION"][buf][buff]["begin"]);
						else pi[j].begin = jToTime(SCH["DEFAULT"][buff]["begin"]);
						if (!SCH["EXCEPTION"][buf][buff]["isdefault"]) pi[j].breakbegin = jToTime(SCH["EXCEPTION"][buf][buff]["breakbegin"]);
						else pi[j].breakbegin = jToTime(SCH["DEFAULT"][buff]["breakbegin"]);
						if (!SCH["EXCEPTION"][buf][buff]["isdefault"]) pi[j].breakend = jToTime(SCH["EXCEPTION"][buf][buff]["breakend"]);
						else pi[j].breakend = jToTime(SCH["DEFAULT"][buff]["breakend"]);
						if (!SCH["EXCEPTION"][buf][buff]["isdefault"]) pi[j].end = jToTime(SCH["EXCEPTION"][buf][buff]["end"]);
						else pi[j].end = jToTime(SCH["DEFAULT"][buff]["end"]);
					}
					ExceptionNum = i+1;
					cout << "Set up schedule for clock widget, from exception No" << ExceptionNum << "." << endl;
					return;
				}
			}
		}
	}
	ParaValue = SCH["DEFAULT"]["paravalue"];
	for (int i=0; i < ParaValue; i++){
		buf[0] = 49+i;
		pi[i].begin = jToTime(SCH["DEFAULT"][buf]["begin"]);
		pi[i].breakbegin = jToTime(SCH["DEFAULT"][buf]["breakbegin"]);
		pi[i].breakend = jToTime(SCH["DEFAULT"][buf]["breakend"]);
		pi[i].end = jToTime(SCH["DEFAULT"][buf]["end"]);
	}
	cout << "Set up schedule for clock widget, from defaultfdgzsf." << endl;
	ExceptionNum = 0;
	//cout << "after schedule" << pi[3].breakbegin.h << pi[3].breakbegin.m << endl;

}

bool WgClock::needUpdateSchedule(){
	char buf[2]; buf[1]='\0';
	DATE start, finish;
	if (SCH["EXCEPTION"]["value"].is_number())
		for (int i=0; i < SCH["EXCEPTION"]["value"]; i++){
			buf[0] = 49+i;
			start = jToDate(SCH["EXCEPTION"][buf]["start"]);
			finish = jToDate(SCH["EXCEPTION"][buf]["finish"]);
			if (NOW.d >= start.d && NOW.m >= start.m  
				&& NOW.d <= finish.d && NOW.m <= finish.m 
				&& ExceptionNum != i+1){
					ExceptionNum = i+1;
					return true;
			}
		}
	else if (ExceptionNum != 0) {ExceptionNum = 0; return true;}
	return false;
}

void WgClock::setParaInfo(){
	for (int i=0; i<ParaValue; i++){
		if ( (HOUR == pi[i].end.h && MIN < pi[i].end.m) || HOUR < pi[i].end.h) {
			sprintf(BUFPARA, "%c. pāra", 49+i); 
			ParaNow = i+1;
			NextParaInfo = pi[i].end;
			return;
		}
	}
	//sprintf(BUFPARA, "%s", "Brīvlaiks");
	sprintf(BUFPARA, "%s", "Brivlaiks");
	NextParaInfo.h = 0; NextParaInfo.m = 0;
	ParaNow = ParaValue+1;
}

void WgClock::setTimerInfo(){
	for (int i=0; i<ParaValue; i++){
		if ( (HOUR == pi[i].begin.h && MIN < pi[i].begin.m) || HOUR < pi[i].begin.h ){
			sprintf(BUFINFO, "Līdz pāra sakumam:");
			int ti = timer(pi[i].begin.h,pi[i].begin.m,0, HOUR, MIN, SEC);
			sprintf(BUFTIMER, "%02d:%02d:%02d", ti/3600, (ti%3600)/60, ti%60);
			return;
		}
		else if ( (HOUR == pi[i].breakbegin.h && MIN < pi[i].breakbegin.m) || HOUR < pi[i].breakbegin.h ){
			sprintf(BUFINFO, "Līdz pārtraukumam:");
			int ti = timer(pi[i].breakbegin.h,pi[i].breakbegin.m,0, HOUR, MIN, SEC);
			sprintf(BUFTIMER, "%02d:%02d:%02d", ti/3600, (ti%3600)/60, ti%60);
			return;
		}
		else if ( (HOUR == pi[i].breakend.h && MIN < pi[i].breakend.m) || HOUR < pi[i].breakend.h ){
			sprintf(BUFINFO, "Pārtraukums:");
			int ti = timer(pi[i].breakend.h,pi[i].breakend.m,0, HOUR, MIN, SEC);
			sprintf(BUFTIMER, "%02d:%02d:%02d", ti/3600, (ti%3600)/60, ti%60);
			return;
		}
		else if ( (HOUR == pi[i].end.h && MIN < pi[i].end.m) || HOUR < pi[i].end.h ){
			sprintf(BUFINFO, "Līdz pāra beigam:");
			int ti = timer(pi[i].end.h,pi[i].end.m,0, HOUR, MIN, SEC);
			sprintf(BUFTIMER, "%02d:%02d:%02d", ti/3600, (ti%3600)/60, ti%60);
			return;
		}
	}
	sprintf(BUFINFO, "Līdz rītdienam:");
	int ti = timer(24,0,0, HOUR, MIN, SEC);
	int hour = ti/3600+pi[0].begin.h, min = (ti%3600)/60+pi[0].begin.m;
	if ((ti%3600)/60+pi[0].begin.m >= 60) {min-=60; hour++;}
	sprintf(BUFTIMER, "%02d:%02d:%02d", hour, min, ti%60);
}

void WgClock::updateMode1(){
	sprintf(BUFTIME, "%02d:%02d", HOUR, MIN);
}

void WgClock::updateMode2(){
	if (HOUR >= NextParaInfo.h && MIN >= NextParaInfo.m && ParaNow != ParaValue+1)
		{setParaInfo();}
}

void WgClock::updateMode3(){
	setTimerInfo();
}

void WgClock::update(){
	setDateTime();
	//HOUR = 12;// MIN += 10;
	if (needUpdateSchedule()) { cout << "Updating clock schedule ... "; setSchedule(); }
	switch (mode){
		case md1x1:{ updateMode1(); break; }
		case md1x2:{ updateMode1(); updateMode2(); break; }
		case md1x3:{ updateMode1(); updateMode2(); updateMode3(); break; }
	}

}

void WgClock::renderMode1()
{
	//WgBackground::render(); // render backgroud of widget
		
	
	FontStorage->getFont((char*)"arialBold")->SetColour(255,255,255);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/1.5);
	FontStorage->getFont((char*)"arialBold")->TextMid(BUFTIME, x + (gridStep.horizontal/2),
		y + (gridStep.vertical/1.5/4));
	
}

void WgClock::renderMode2(){
	FontStorage->getFont((char*)"arialBold")->SetColour(0, 85, 81);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/3);
	FontStorage->getFont((char*)"arialBold")->TextMid(BUFPARA, x + (gridStep.horizontal/2),
				  y - gridStep.vertical/3*2);
}

void WgClock::renderMode3(){
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/5);
	FontStorage->getFont((char*)"arialBold")->TextMid(BUFINFO, x + (gridStep.horizontal/2),
				 y - gridStep.vertical - (gridStep.vertical/5/2));
	setTextColor(color);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/2.2);
	FontStorage->getFont((char*)"arialBold")->TextMid(BUFTIMER, x + (gridStep.horizontal/2), 
				 y - gridStep.vertical - (gridStep.vertical/4)*3);
}

void WgClock::render(){	
		//cout << "5" << endl;

	WgBackground::render();
	switch (mode){
		case md1x1:{ renderMode1(); break; }
		case md1x2:{ renderMode1(); renderMode2(); break; }
		case md1x3:{ renderMode1(); renderMode2(); renderMode3(); break; }
	}
		//cout << "6" << endl;

}
