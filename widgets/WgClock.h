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

#include "iostream"
#include "fstream"
#include "cstring"

class WgClock : public WgBackground
{
private:
	time_t rawtime;
	struct tm * timeinfo;
	int YEAR, DAY, HOUR, MIN, SEC, NOW;
	char MOUNTH[100], WEEK[100];
	char BUFTIME[10];
	
public:
	WgClock(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
	~WgClock() {};
	
	void update();
	void render();
};
