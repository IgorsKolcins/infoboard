#include "WgForecast.h"
#include "../CPicturesStorage.h"
#include "../CFontStorage.h"


WgForecast::WgForecast(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode):
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	updateTime = 600;
	update();
}

WgForecast::~WgForecast()
{
}

size_t WgForecast::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) //???
{
    ((std::string*)userp)->append((char*)contents, size * nmemb); // ???
    return size * nmemb; // ???
}

void WgForecast::getWeatherFromWeb(char site[])
{	
	/*
	//--CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter)
	//----	CURL *handle - указатель на интерфейс, который мы получили выше.
	//----	CURLoption option - название опции, которую следует задать.
	//----	parameter - параметр, который связывается с опцией, это может быть число, у
	//		казатель на функцию, строка. Функцию можно вызывать несколько раз подряд,
	//		задавая необходимые опции. Все опции, по умолчанию, выключены.
	
	//--CURLOPT_URL - очень важная опция, в параметре указывается строка - URL,
	//	с которым собираемся взаимодействовать. В строке параметра можно указать небходимый протокол,
	//	в виде стандартного префикса "http://" или "ftp://". 
	
	//--CURLOPT_WRITEFUNCTION - данная опция позволяет задавать,
	//	в качестве параметра, указатель на функцию обратного вызова. 
	//	Эта функция вызывается библиотекой, каждый раз, когда принимаются какие либо данные,
	//	требующие дальнейшего использования или сохранения.
	
	//--CURLOPT_WRITEDATA - эта опция определяет параметр, как объект,
	//	в который производится запись принимаемых данных.
	
	//--void curl_easy_cleanup(CURL * handle) - Это функция должна вызываться самой последней
	//	и вызываться должна обязательно. Она выполняет завершение текущей сессии.
	*/
	
	CURL *curl; // object CURL tipa
	std::string readBuffer; //буффур куда будем записывать принятые данные
	CURLcode res;
	static char errorBuffer[CURL_ERROR_SIZE]; //объявляем буфер, для хранения возможной ошибки, размер определяется в самой библиотеке
	
	curl = curl_easy_init(); // curl initialization

	if (curl) //проверяем
	{
		//задаем все необходимые опции	
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer); //определяем, куда выводить ошибки
		
		curl_easy_setopt(curl, CURLOPT_URL, site); //задаем опцию - получить страницу по адресу site
		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //указываем функцию обратного вызова для записи получаемых данных
		
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); //указываем куда записывать принимаемые данные
		
		res = curl_easy_perform(curl); //запускаем выполнение задачи
				
		
			if (res == CURLE_OK)
			{
				auto buf = json::parse(readBuffer);
				weatherData = buf;
				#ifdef ONDEBUG
					cout << readBuffer << endl;
				#endif              
			}
			else  
			{    
				isConnection = false;
				//выводим сообщение об ошибке
				cout << "Error! " << errorBuffer << endl;
			}
		
	}
	
	curl_easy_cleanup(curl); //выполняем обязательное завершение сессии
	
	
}


void WgForecast::updateMode1()
{
	getWeatherFromWeb((char*)"http://api.openweathermap.org/data/2.5/weather?q=Daugavpils&units=metric&appid=a0a20199a69ae584fd1303a3152d92bc");
	if (isConnection)
	{
		int bufTemp = weatherData["main"]["temp"];
		sprintf(temp, "+%d", bufTemp); //°
	}
	else
		sprintf(temp, "err");
}

void WgForecast::updateMode2()
{
	if (isConnection)
	{
		windDegree = weatherData["wind"]["deg"];
		float bufSpeed = weatherData["wind"]["speed"];
		sprintf(windSpeed, "%4.2f m/s", bufSpeed);
	}
	else
	{
		sprintf(windSpeed, "err");
		windDegree = 0;
	}
	/*if (isConnection)
	{
		//string weatherBuf = weatherData["weather"]["description"][1];
		//sprintf(weatherInfo, "%s", bufInfo.c_str());
		//weatherInfo = new char[bufInfo.length()+1];
		//strcpy(weatherInfo, bufInfo.c_str());
		//weatherInfo = new char[bufInfo.length()+1];
	}
	else
		sprintf(weatherInfo, "err");*/
}

void WgForecast::updateMode3()
{
	if (isConnection)
	{
		windDegree = weatherData["wind"]["deg"];
		float bufSpeed = weatherData["wind"]["speed"];
		sprintf(windSpeed, "%4.2f m/s", bufSpeed);
	}
	else
	{
		sprintf(windSpeed, "err");
		windDegree = 0;
	}
}

void WgForecast::update()
{
	switch (mode){
		case md1x1:{ updateMode1(); break; }
		case md1x2:{ updateMode1(); updateMode2(); break; }
		case md1x3:{ updateMode1(); updateMode2(); updateMode3(); break; }
	}
}

void WgForecast::renderMode1()
{
	FontStorage->getFont((char*)"arialBold")->SetColour(255,255,255);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/1.5);
	FontStorage->getFont((char*)"arialBold")->TextMid(temp, x + (gridStep.horizontal/2),
		y + (gridStep.vertical/1.5/4));
}

void WgForecast::renderMode2()
{
	setTextColor(clHaki);
	//setTextColor(color);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/2.8);
	FontStorage->getFont((char*)"arialBold")->TextMid(windSpeed, x + (gridStep.horizontal/2.5),
				  y - gridStep.vertical/16*11);
	PicStorage->Arrow->render(x + (gridStep.horizontal/1.3), y - gridStep.vertical/1.4, 1, 1, 0,0,-windDegree);

	/*setTextColor(clHaki);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/3);
	FontStorage->getFont((char*)"arialBold")->TextMid("apraksts", x + (gridStep.horizontal/2),
				  y - gridStep.vertical/16*11);*/
}

void WgForecast::renderMode3()
{
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/5);
	FontStorage->getFont((char*)"arialBold")->TextMid("Veišs:", x + (gridStep.horizontal/2),
				 y - gridStep.vertical - (gridStep.vertical/5/2));
	setTextColor(color);
	FontStorage->getFont((char*)"arialBold")->SetSize(gridStep.vertical/2.8);
	FontStorage->getFont((char*)"arialBold")->TextMid(windSpeed, x + (gridStep.horizontal/2.5),
				  y - gridStep.vertical - gridStep.vertical/16*11);
	PicStorage->Arrow->render(x + (gridStep.horizontal/1.3), y - gridStep.vertical - gridStep.vertical/1.4, 1, 1, 0,0,-windDegree);
}

void WgForecast::render()
{
	if (isConnection)
	{
		WgBackground::render();
		
		switch (mode){
			case md1x1:{ renderMode1(); break; }
			case md1x2:{ renderMode1(); renderMode2(); break; }
			case md1x3:{ renderMode1(); renderMode2(); renderMode3(); break; }
		}
	}
}

