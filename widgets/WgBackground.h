/* WgBackground Author: Igors Kolcins
*-- This is visual widget.
*		This widget render only backgroud of widget with shadows
*		and have empety update.
*/
#pragma once
#include "IWidget.h"

#define UPDATE_TIME_SEK 5

#define GRID_VERTICAL 10//8.3333
#define GRID_HORIZONTAL 6//5


enum wgColor {clWhite, clBlue, clCyan, clGreen, clHighBlue, clHighPurple, clLazyYellow, clOrange, clPurple, clYellow, clHaki};
enum wgMode {md1x1 = 1, md1x2, md1x3, md2x8};

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
	bool isShadows; //on/off shadows
	
private: 
	
	
public:
	WgBackground(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
    ~WgBackground();
    
    void setFillColor(wgColor c); //set color of block with command Fill
    
    void setTextColor(wgColor c); //set color of text
    
    void render();
    void update() {};
};
