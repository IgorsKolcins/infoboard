/* WgBackground
*-- This is visual widget.
*		This widget render only backgroud of widget with shadows
*		and have empety update.
*/
#pragma once
#include "IWidget.h"

#define UPDATE_TIME_SEK 5


enum wgColor {clWhite, clBlue, clCyan, clGreen, clHighBlue, clHighPurple, clLazyYellow, clOrange, clPurple, clYellow};
enum wgMode {md1x1 = 1, md1x2, md1x3};

struct scrGrid {
	int horizontal; 
	int vertical;
};

class WgBackground : public IWidget
{

protected:
	int scrWidth, scrHeight; //screen resolution
	int posX, posY; //position in the grid
	wgMode mode; //widget mode
	scrGrid gridStep; //one grid step
	int x,y; //coordinates
	int sizeX, sizeY; //widget size in the grid, example: sizeX=1; sizeY=1; fill only one block in the grid
	wgColor color;
	
private: 
	
	
public:
	WgBackground(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
    ~WgBackground();
    
    void setFillColor(wgColor c); //set color of block with command Fill
    void setTextColor(wgColor c);
    
    void render();
    void update() {};
};
