#include "engine.h"


int main()
{
	int width, height;
	init(&width, &height);
	
	
	Engine *engine = new Engine(width, height);

	engine->start();
	
	delete engine;
	
	return 0;
}
