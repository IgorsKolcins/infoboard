#include "WgAds.h"

#include "../CPicturesStorage.h" //use pictures PicStorage->...
#include "../CFontStorage.h" //use text FontStorage->getFont((char*)"arialBold")->..

WgAds::WgAds(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode):
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	if (mode == md2x8) { sizeX = 3; sizeY = 8; } //size of widget
	isShadows = false; //shadows off
	updateTime = 1; //update time
	update(); //first update
}

WgAds::~WgAds()
{
	
}

void WgAds::update()
{
	sprintf(ads, "default");
}

void WgAds::render()
{
	WgBackground::render(); //render background
	
	FontStorage->getFont((char*)"arialBold")->SetColour(255,255,255);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/1.5);
	FontStorage->getFont((char*)"arialBold")->TextMid("Sludinajumi", x + (gridStep.horizontal*1.5),
		y + (gridStep.vertical/1.5/4));
		
		
	setTextColor(clHaki);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/3);
	FontStorage->getFont((char*)"arialBold")->TextMid(ads, x + (gridStep.horizontal/2),
				  y - gridStep.vertical/16*11);
}
