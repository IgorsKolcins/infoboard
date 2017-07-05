//WgWeather
#pragma once
#include "WgBackground.h" // Backgroud of widget
#include "curl/curl.h"
//#include "../lib/json.h"
#include <iostream>
#include <string>

using namespace std;
//using json = nlohmann::json;

class WgWeather : public WgBackground
{
private:
	//char site[]="http://api.openweathermap.org/data/2.5/weather?q=Daugavpils&units=metric&appid=a0a20199a69ae584fd1303a3152d92bc";
	char weathertype[50];
	char icon[10];
	float  speed, deg; 
	char temp[10];
	
	char bufTemp[100], bufSpeed[10];
	
	//json weather;
	
	void renderMode1();
	void renderMode2();
	void renderMode3();
	
	void updateMode1();
	void updateMode2();
	void updateMode3();
	
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	void getWeatherFromWeb(char site[]);

	
public:
	WgWeather(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode);
	~WgWeather() {};
	
	void update();
	void render();
};
