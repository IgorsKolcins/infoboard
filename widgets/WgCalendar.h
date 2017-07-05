#pragma once

#include "WgBackground.h" // Backgroud of widget


using namespace std;

class WgCalendar : public WgBackground
{
private:
	time_t rawtime;
    struct tm * timeinfo;
    
	int YEAR, DAY, HOUR, MIN, SEC;
    char MOUNTH[100], WEEK[100], WDAY[100];
    
    char BUFDATE[10], BUFDAY[20], BUFWEEK[100];
    
    void renderMode1();
	void renderMode2();
	void renderMode3();
	
	void updateMode1();
	void updateMode2();
	void updateMode3();
	
	void setDateTime();
	const char* getWDay(char * wday);
	
public:
	WgCalendar(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode);
	~WgCalendar() {};
	
	void update();
	void render();
};
