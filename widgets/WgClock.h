/*WgClock
*-- This is visual widget.
*		His only update time and render it.
*		Background render parent class WgBackground
* 
*--  -- Modes: it has 3 modes
*			md1x1: show only time
*			md1x2: show time and current lecture
*			md1x3: show time, current lecture and show timer to the next lecture
*/
#pragma once
#include "WgBackground.h"

#include "../lib/json.h"

#include "iostream"
#include "fstream"
#include "cstring"

using namespace std;
using json = nlohmann::json;

class WgClock : public WgBackground
{
private:
	struct DATE{
		int d = 0;
		int m = 0;
	};

	struct TIME{
		int h = 0;
		int m = 0;
	};

	struct PARA{
		TIME begin;
		TIME breakbegin;
		TIME breakend;
		TIME end;
	};

	PARA pi[10];
	DATE NOW;

	time_t rawtime;
	struct tm * timeinfo;
	int YEAR, DAY, HOUR, MIN, SEC;
	char MOUNTH[100], WEEK[100];

    	char BUFTIME[10], BUFPARA[10], BUFTIMER[10], BUFINFO[100], BUFINFO2[100];
	int ExceptionNum;
	int ParaValue;
	TIME NextParaInfo; //NextParaInfo.h = 0; NextParaInfo.m = 0;
	int ParaNow = 0;

	json SCH;

	int timer(int hour1, int min1, int sec1, int hour2 ,int min2, int sec2);	
	struct TIME jToTime(double j);
	struct DATE jToDate(double j);
	bool needUpdateSchedule();
	
	void setDateTime();
	void setParaInfo();
	void setTimerInfo();
	
	void renderMode1();
	void renderMode2();
	void renderMode3();
	
	void updateMode1();
	void updateMode2();
	void updateMode3();
	
public:
	WgClock(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
	~WgClock() {};
	
	void update();
	void render();
	
	void setSchedule();
	void readFile(json &aj, char *FileName = (char*)"resources/clockSchedule.json");
};

