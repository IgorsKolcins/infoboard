/*WgForecast Author: Igors Kolcins
*-- This is visual widget.
*		Show forecast for now.
*		Background render parent class WgBackground
* 
*--  -- Modes: it has 1 modes
*			md1x1: show temperature
*/
#pragma once
#include "WgBackground.h"

#include "curl/curl.h"
// git: github.com/curl/curl
// Some basic information at the russian: http://www.programmersforum.ru/showthread.php?t=60338

#include "../lib/json.h"
using json = nlohmann::json;
// examples and wiki: https://github.com/nlohmann/json

#include "iostream"

using namespace std;


//#define ONDEBUG

class WgForecast : public WgBackground
{
private:
		
	//char site[]="http://api.openweathermap.org/data/2.5/weather?q=Daugavpils&units=metric&appid=a0a20199a69ae584fd1303a3152d92bc";	
		
	json weatherData;
	
	char temp[5]; //temperature
	char windSpeed[10]; //wind speed
	int windDegree; //wind degree
	char weatherInfo[50]; //information about weather
	
	bool isConnection = true;
		
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
	void getWeatherFromWeb(char site[]);	
		
	void renderMode1();
	void renderMode2();
	void renderMode3();
	
	void updateMode1();
	void updateMode2();
	void updateMode3();
	
public:
	WgForecast(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
	~WgForecast();
	
	void update();
	void render();
};
