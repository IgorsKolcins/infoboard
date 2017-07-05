#include "WgCalendar.h"
#include "../CFontStorage.h"

#include "iostream"

using namespace std;

WgCalendar::WgCalendar(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode):
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	updateTime = 60;
	update();
}

WgCalendar::~WgCalendar()
{
	
}

const char* WgCalendar::convertWeekDayFromInt(int wday)
{
	switch (wday)
	{
		case 0: return "Pirmdiena";
		case 1: return "Otrdiena";
		case 2: return "Trešdiena";
		case 3: return "Ceturtdiena";
		case 4: return "Piektdiena";
		case 5: return "Sestdiena";
		case 6: return "Svētdiena";
		default: return "Error";
	}
}

const char* WgCalendar::convertMounthFromInt(int mon)
{
	switch (mon)
	{
		case 0: return "Jan";
		case 1: return "Feb";
		case 2: return "Mar";
		case 3: return "Apr";
		case 4: return "Mai";
		case 5: return "Jūn";
		case 6: return "Jūl";
		case 7: return "Aug";
		case 8: return "Sep";
		case 9: return "Okt";
		case 10: return "Nov";
		case 11: return "Dec";
		default: return "Err";
	}
}


void WgCalendar::updateMode1()
{
	sprintf(bufDate, "%i. %s", ptr->tm_mday, convertMounthFromInt(ptr->tm_mon));
}

void WgCalendar::updateMode2()
{
	sprintf(bufWeekDay, "%s", convertWeekDayFromInt(ptr->tm_wday));
}

void WgCalendar::updateMode3()
{
	strftime(bufWeek, 5, "%W", ptr);
}

void WgCalendar::update()
{
	cout << "update calendar" << endl;
	lt = time(NULL);
	ptr = localtime(&lt);
	
	switch (mode){
		case md1x1:{ updateMode1(); break; }
		case md1x2:{ updateMode1(); updateMode2(); break; }
		case md1x3:{ updateMode1(); updateMode2(); updateMode3(); break; }
	}
}

void WgCalendar::renderMode1()
{
	FontStorage->getFont((char*)"arialBold")->SetColour(255,255,255);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/1.5);
	FontStorage->getFont((char*)"arialBold")->TextMid(bufDate, x + (gridStep.horizontal/2),
		y + (gridStep.vertical/1.5/4));
}

void WgCalendar::renderMode2()
{
	setTextColor(clHaki);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/3);
	FontStorage->getFont((char*)"arialBold")->TextMid(bufWeekDay, x + (gridStep.horizontal/2),
				  y - gridStep.vertical/16*11);
}

void WgCalendar::renderMode3()
{
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/5);
	FontStorage->getFont((char*)"arialBold")->TextMid("Nedeļa skaits gadā:", x + (gridStep.horizontal/2),
				 y - gridStep.vertical - (gridStep.vertical/5/2));
	setTextColor(color);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/2.2);
	FontStorage->getFont((char*)"arialBold")->TextMid(bufWeek, x + (gridStep.horizontal/2), 
				 y - gridStep.vertical - (gridStep.vertical/4)*3);
}

void WgCalendar::render()
{
	WgBackground::render();
	
	switch (mode){
		case md1x1:{ renderMode1(); break; }
		case md1x2:{ renderMode1(); renderMode2(); break; }
		case md1x3:{ renderMode1(); renderMode2(); renderMode3(); break; }
	}
}
