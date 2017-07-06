#include "WgForecast.h"
#include "../CFontStorage.h"
#include "iostream"

using namespace std;

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
				
		#ifdef ONDEBUG
			if (res == CURLE_OK)      
				//выводим полученные данные на стандартный вывод (консоль)
				cout << readBuffer << endl;              
			else      
				//выводим сообщение об ошибке
				cout << "Error! " << errorBuffer << endl;
		#endif
	}
	
	curl_easy_cleanup(curl); //выполняем обязательное завершение сессии
	
	auto buf = json::parse(readBuffer);
	weatherData = buf;
}


void WgForecast::updateMode1()
{
	getWeatherFromWeb((char*)"http://api.openweathermap.org/data/2.5/weather?q=Daugavpils&units=metric&appid=a0a20199a69ae584fd1303a3152d92bc");
	int buf = weatherData["main"]["temp"];
	sprintf(bufTemp, "+%d°", buf);
}

void WgForecast::updateMode2()
{
}

void WgForecast::updateMode3()
{
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
	FontStorage->getFont((char*)"arialBold")->TextMid(bufTemp, x + (gridStep.horizontal/2),
		y + (gridStep.vertical/1.5/4));
}

void WgForecast::renderMode2()
{
}

void WgForecast::renderMode3()
{
}

void WgForecast::render()
{
	WgBackground::render();
	
	switch (mode){
		case md1x1:{ renderMode1(); break; }
		case md1x2:{ renderMode1(); renderMode2(); break; }
		case md1x3:{ renderMode1(); renderMode2(); renderMode3(); break; }
	}
}

