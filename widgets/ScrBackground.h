#pragma once
#include "../lib/Picture.h"

class ScrBackground
{

private:
	Picture *image;
	//int w, h;
	float sclx, scly;
	
public:
	ScrBackground();
	ScrBackground(int w, int h);
    ~ScrBackground();
    void render();
    void update();

};
