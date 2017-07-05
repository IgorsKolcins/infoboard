//WgWeather
#pragma once
#include "WgBackground.h" // Backgroud of widget
using namespace std;

//#define USERS_COUNT 17

class WgKpnference : public WgBackground
{
private:
	//char nr[USERS_COUNT][255];
	Picture *saraksts;
	void render1();

	
public:
	WgKpnference(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode);
	~WgKpnference() { delete saraksts; };
	
	void update();
	void render();
};
