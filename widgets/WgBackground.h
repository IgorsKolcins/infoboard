#pragma once
#include "../lib/Picture.h"
#include "../lib/TFont/TFont.h"
#include "iostream"
#include "IWidget.h"

#define UPDATE_TIME_SEK 5


using namespace std;

enum wgColor {clWhite, clBlue, clCyan, clGreen, clHighBlue, clHighPurple, clLazyYellow, clOrange, clPurple, clYellow};
enum wgMode {md1x1 = 1, md1x2, md1x3, md2x8};

struct wgShadow {
	bool top; 
	bool bot; 
	bool left; 
	bool right;
};
	
struct scrGrid {
	int horizontal; 
	int vertical;
};

struct wgShadowPictures{
	Picture *t;
	Picture *b;
	Picture *l;
	Picture *r;
	Picture *lt;
	Picture *lb;
	Picture *rb;
	Picture *rt;
};

class WgBackground : public IWidget
{

protected:
	int scrWidth, scrHeight;
	int x, y;
	wgColor color;
	wgMode mode;
	wgShadow shadows;
	wgShadowPictures shadowsPictures;
	scrGrid oneGridStep;
	int sizeX, sizeY;
	TFont *text;
	
	void setTextColor(wgColor c);
	void setFillColor(wgColor c);
	
	bool grid = true;
	int posx;
	int posy;
	
		
private: 
	
	
public:
	WgBackground(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode);
    ~WgBackground();
    
    void update() {};
	void render();
	
    void setScr(int AscrWidth, int AscrHeight) { scrWidth = AscrWidth; scrHeight = AscrHeight;};
    void setPos(int Ax, int Ay) {x = Ax; y = Ay; };
    void setMode(wgMode Amode) {mode = Amode;};
    void setColor(wgColor Acolor) {color = Acolor;};
    void setShadows(wgShadow Ashadows) {shadows=Ashadows;};
    void setGrid(int Ahorizontal, int Avertical) { oneGridStep.horizontal = scrWidth/Ahorizontal;  oneGridStep.vertical = scrHeight/Avertical;};
	void setUpdTime(float Asek) {updateTime = Asek;};
	void setXY(int Ax, int Ay) { posx = Ax; posy = Ay; grid = false; };

};
