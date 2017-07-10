#include "WgAds.h"

#include <string>
#include <dirent.h>

#include "../CPicturesStorage.h" //use pictures PicStorage->...
#include "../CFontStorage.h" //use text FontStorage->getFont((char*)"arialBold")->..



WgAds::WgAds(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode):
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	system("touch ./widgets/text/flag");
	if (mode == md2x8) { sizeX = 3; sizeY = 8; } //size of widget
	isShadows = false; //shadows off
	updateTime = 1; //update time
	isAds = false;
	//update(); //first update
}

WgAds::~WgAds()
{
	
}

bool WgAds::readFile(char *text)
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
				FILE *file = fopen("./widgets/text/text.txt", "rb");
				
				fseek(file, 0, SEEK_END);
				int size = ftell(file);
				
				fclose(file);
				
				file = fopen("./widgets/text/text.txt", "rb");
				fread(text, 1, size, file);
				
				fclose(file);
				system("rm -rf ./widgets/text/flag");
				return true;
			}
		}
	return false;
}

int WgAds::Separate( char * Src, char ** Dst = NULL )
{
	int p = 0;
	if (Dst) Dst[p] = Src;
	for ( ; *Src; Src++) {
		if (*Src == '\n') { 
			*Src = '\0';
			char * str = Src + 1; 
			while (*str == '\r') *str++; 
			if (Dst) Dst[++p] = str; else p++;
		}
	}
	return p;
}
void WgAds::update()
{
	if (readFile(ads)) 
	{
		lineCount = Separate(ads, adsPeace);
		//cout << lineCount << endl;
		isAds = true;
	}
	
	/*if (true)
	{
		cout << "text width: " << FontStorage->getFont((char*)"arialBold")->TextWidth(ads) << endl;
		cout << "grid step: " << gridStep.horizontal << endl;
		cout << "size X: " << sizeX << endl;
		cout << "str len: " << strlen(ads) << endl;
		

		double lineCount = FontStorage->getFont((char*)"arialBold")->TextWidth(ads)/(gridStep.horizontal*sizeX);
		int symbolsInLine = strlen(ads)/lineCount;
		
		cout << "symbols: " << symbolsInLine << endl;
		cout << "lines: " << lineCount << endl;

		//strncpy(adsPeace, ads, symbolsInLine);
		for (int i=0; i<lineCount; i++)
		{
			//for (int i=0; i<symbolsInLine; i++)
			cout << i << endl;
		}
	}*/
}

void WgAds::render()
{
	WgBackground::render(); //render background
	
	FontStorage->getFont((char*)"arialBold")->SetColour(255,255,255);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/1.5);
	FontStorage->getFont((char*)"arialBold")->TextMid("Sludinajumi", x + (gridStep.horizontal*1.5),
		y + (gridStep.vertical/1.5/4));
		
	
		
	setTextColor(clHaki);
	int size = gridStep.vertical/3;
	if (lineCount < 7) size*=1.5;
	if (lineCount > 14) size/=2; 
	FontStorage->getFont((char*)"arialBold")->SetSize(size);
	
	int lineY = y - gridStep.vertical;
	if (isAds) for (int i=0; i<lineCount; i++) 
	{
		FontStorage->getFont((char*)"arialBold")->TextMid(adsPeace[i], x + (gridStep.horizontal*sizeX)/2, lineY);
		lineY-=size*1.2;
	}
}
