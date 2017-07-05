#include "WgClock.h"
#include "../CFontStorage.h"

WgClock::WgClock(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode) :
	WgBackground(AscrWidth, AscrHeight, AposX, AposY, Amode)
{
	updateTime = 0.25;
	this->update();
}

void WgClock::update()
{
	time(&rawtime);
    timeinfo = localtime(&rawtime);
    sscanf(asctime(timeinfo), "%[^ ] %[^ ] %d %d:%d:%d %d", WEEK, MOUNTH, &DAY, &HOUR, &MIN, &SEC, &YEAR);  
    sprintf(BUFTIME, "%02d:%02d", HOUR, MIN);
}

void WgClock::render()
{
	WgBackground::render(); // render backgroud of widget
		
	
	FontStorage->getFont((char*)"arialBold")->SetColour(255,255,255);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/1.5);
	FontStorage->getFont((char*)"arialBold")->TextMid(BUFTIME, x + (gridStep.horizontal/2),
		y + (gridStep.vertical/1.5/4));
	
	
	/*
	FontStorage->fonts[0]->fontFile->SetColour(255,255,255);
	FontStorage->fonts[0]->fontFile->SetSize(gridStep.vertical/1.5);
	FontStorage->fonts[0]->fontFile->TextMid(BUFTIME, x + (gridStep.horizontal/2),
		y + (gridStep.vertical/1.5/4));
	*/
}
