#include "WgAds.h"

#include <cstring>
#include <dirent.h>

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
	struct dirent **namelist;
	int n;
	
	n = scandir("./widgets/text/", &namelist, NULL, alphasort);
	if (n < 0) perror("scandir");
	else
		while(n--)
		{
			if(strcmp(namelist[n]->d_name, "flag") == 0)
			{
				FILE *file = fopen("./widgets/text/text.txt", "rt");
				
				fseek(file, 0, SEEK_END);
				int size = ftell(file);
				
				fclose(file);
				
				file = fopen("./widgets/text/text.txt", "rb");
				fread(ads, 1, size, file);
				
				fclose(file);
				system("rm -rf ./widgets/text/flag");
			}
		}
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
