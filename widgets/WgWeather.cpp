#include "WgWeather.h"

WgWeather::WgWeather(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode) : 
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	setUpdTime(1);
	setColor(clPurple);
	update();	
}

size_t WgWeather::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void WgWeather::getWeatherFromWeb(char site[])
{
	CURL *curl;
	std::string readBuffer;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		

		curl_easy_setopt(curl, CURLOPT_URL, site);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);	
		curl_easy_cleanup(curl);
				
		/*using json = nlohmann::json;
		auto j = json::parse(readBuffer);
		
		temp = j["list"]["weather"]["id"];*/
				
		sscanf(readBuffer.c_str(),"{\"coord\":{\"lon\":%*[^,],\"lat\":%*[^}]},\"weather\":[{\"id\":%*[^,],\"main\":\"%*[^\"]\",\"description\":\"%[^\"]\",\"icon\":\"%[^\"]\"}],\"base\":\"%*[^\"]\",\"main\":{\"temp\":%[^.]%*[^w]wind\":{\"speed\":%f,\"deg\":%f",weathertype, icon, temp, &speed, &deg);   // " 34
	}
	
}

void WgWeather::updateMode1(){
	sprintf(bufTemp, "+%d°", 12);//, temp);
}

void WgWeather::updateMode2(){
	sprintf(bufSpeed, "%.1f m/s", speed);
}
void WgWeather::updateMode3(){
	
}


void WgWeather::update(){
	//cout << "Update weather ...";
	//getWeatherFromWeb((char*)"http://api.openweathermap.org/data/2.5/weather?q=Daugavpils&units=metric&appid=a0a20199a69ae584fd1303a3152d92bc");
	updateMode1();
	updateMode2();
	//cout << "complete!" << endl;
	
	
	
}


void WgWeather::renderMode1(){
	text->SetColour(255,255,255);
	text->SetSize(oneGridStep.vertical/2);
	text->TextMid(bufTemp, posx + (oneGridStep.horizontal/2),
		posy + (oneGridStep.vertical/4));
	
}

void WgWeather::renderMode2(){
	text->SetColour(0, 85, 81);
	text->SetSize(oneGridStep.vertical/3);
	text->TextMid(bufSpeed, posx + (oneGridStep.horizontal/2),
				 posy - oneGridStep.vertical/3*2);
}

void WgWeather::renderMode3(){

}


void WgWeather::render(){
	WgBackground::render();
	
	switch (mode){
		case md1x1:{ renderMode1(); break; }
		case md1x2:{ renderMode1(); renderMode2(); break; }
		case md1x3:{ renderMode1(); renderMode2(); renderMode3(); break; }
	}	
	
}
