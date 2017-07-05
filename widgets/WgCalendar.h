/*WgCalendar Author: Igors Kolcins
 *--This visual widget
 * 
 */
#pragma once
#include "WgBackground.h"
#include "ctime"

class WgCalendar : public WgBackground
{
private:
	time_t lt;
	struct tm *ptr;
	
	char bufDate[32], bufWeekDay[32], bufWeek[32]; 
	
	const char* convertWeekDayFromInt(int wday);
	const char* convertMounthFromInt(int mon);
	
	void renderMode1();
	void renderMode2();
	void renderMode3();
	
	void updateMode1();
	void updateMode2();
	void updateMode3();
	
public:
	WgCalendar(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
	~WgCalendar();
	
	void update();
	void render();
};
