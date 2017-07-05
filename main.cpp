#include "engine.h"

//--Storages
#include "CPicturesStorage.h"
#include "CFontStorage.h"



int main()
{
	int width, height;
	init(&width, &height);
	
	PicStorage = new CPicturesStorage();
	FontStorage = new CFontStorage();
	FontStorage->setFont((char*)"arialBold", (char*)"lib/TFont/ArialBold.ttf");
	
	Engine *engine = new Engine(width, height);

	engine->start();
	
	delete engine;
	
	delete FontStorage;
	delete PicStorage;
	
	return 0;
}
