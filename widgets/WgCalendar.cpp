#include "WgCalendar.h"

 WgCalendar::WgCalendar(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode):
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	setUpdTime(60);
	setColor(clOrange);
	update();
}

const char* WgCalendar::getWDay(char * wday){
	if ( ! strcmp(wday, "Mon") ) return "Pirmdiena";
	else if ( ! strcmp(wday, "Tue") ) return "Otrdiena";
	else if ( ! strcmp(wday, "Wed") ) return "Trešdiena";
	else if ( ! strcmp(wday, "Thu") ) return "Ceturtdiena";
	else if ( ! strcmp(wday, "Fri") ) return "Piektdiena";
	else if ( ! strcmp(wday, "Sat") ) return "Sestdiena";
	else if ( ! strcmp(wday, "Sun") ) return "Svētdiena";
	return "Error";
}

void WgCalendar::setDateTime(){
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sscanf(asctime(timeinfo), "%[^ ] %[^ ] %d %d:%d:%d %d", WEEK, MOUNTH, &DAY, &HOUR, &MIN, &SEC, &YEAR);
}

void WgCalendar::updateMode1(){
	sprintf(BUFDATE, "%02d. %s", DAY, MOUNTH);
}

void WgCalendar::updateMode2(){
	sprintf(BUFDAY, "%s", getWDay(WEEK));
}

void WgCalendar::updateMode3(){
	//char* format = "%W";
	//strftime(BUFWEEK, 5, format, timeinfo);
	sprintf(BUFWEEK, "%i. nedela", 1);
}

void WgCalendar::update() {
	setDateTime();
	switch (mode){
		case md1x1:{ updateMode1(); break; }
		case md1x2:{ updateMode1(); updateMode2(); break; }
		case md1x3:{ updateMode1(); updateMode2(); updateMode3(); break; }
	}
}

void WgCalendar::renderMode1(){
	text->SetColour(255,255,255);
	text->SetSize(oneGridStep.vertical/2);
	text->TextMid(BUFDATE, posx + (oneGridStep.horizontal/2),
		posy + (oneGridStep.vertical/4));
}

void WgCalendar::renderMode2(){
	text->SetColour(0, 85, 81);
	text->SetSize(oneGridStep.vertical/3);
	text->TextMid(BUFDAY, posx + (oneGridStep.horizontal/2),
				  posy - oneGridStep.vertical/16*11);
}

void WgCalendar::renderMode3(){
	text->SetSize(oneGridStep.vertical/5);
	text->TextMid("Saraksts:", posx + (oneGridStep.horizontal/2),
				 posy - oneGridStep.vertical - (oneGridStep.vertical/5/2));
	setTextColor(color);
	text->SetSize(oneGridStep.vertical/2.2);
	text->TextMid(BUFWEEK, posx + (oneGridStep.horizontal/2), 
				 posy - oneGridStep.vertical - (oneGridStep.vertical/4)*3);
}

void WgCalendar::render(){
	WgBackground::render();
	switch (mode){
		case md1x1:{ renderMode1(); break; }
		case md1x2:{ renderMode1(); renderMode2(); break; }
		case md1x3:{ renderMode1(); renderMode2(); renderMode3(); break; }
	}
}
