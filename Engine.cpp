#include "engine.h"

Engine::Engine(int width, int height)
{
	board = new Board();
	isRunning = false;
	this->width = width;
	this->height = height;
	frameCap = 1.0 / FRAMES_PER_SECOND;
	firstTime = 0;
	lastTime = clock() / (double)CLOCKS_PER_SEC;
	updateTime = lastTime;
	passedTime = 0;
	unprocessedTime = 0;
	oneSecTime = 0;
	updateTime = 0;
	frames = 0;
	fps = 0;
}

Engine::~Engine()
{
	delete board;
}

void Engine::start()
{
	if(isRunning) return;
	
	run();
}

void Engine::run()
{	
	isRunning = true;
	while(isRunning)
	{
		kbhit();  //?
		
		firstTime = clock() / (double)CLOCKS_PER_SEC;		
		
		if(firstTime < lastTime && lastTime > 0) passedTime = 0.0001;
		else passedTime = firstTime - lastTime;
		lastTime = firstTime;
		
		
		unprocessedTime += passedTime;
		oneSecTime += passedTime;
		updateTime += passedTime;
		
		/////////
		update(); //?
		/////////
		
		if(unprocessedTime >= frameCap)
		{
			// 25 frames per second
			
			unprocessedTime -= frameCap;
			
			////////
			render();
			////////
			
			showFrames();
		}
		frames++;
		
	}
}

void Engine::update()
{
	//////////////////////////////////////////////////////
	/*				UPDATE DATA HERE					*/
	
	double maxUpdateTime = 0;
	
	w = board->findFirst();
	if(w) maxUpdateTime = w->getUpdateTime();
	
	while (w) 
	{	
		if(fmod(updateTime, (double)w->getUpdateTime()) > 0 && fmod(updateTime, (double)w->getUpdateTime()) < 0.0001) 
		{
			w->update();
		}
		
		w = board->findNext();
		
		if(w) 
		{
			if(maxUpdateTime < w->getUpdateTime()) maxUpdateTime = w->getUpdateTime();
		}
		else updateTime = 0.0;
	}
	if(updateTime >= maxUpdateTime) updateTime = 0.0;
	
	/////////////////////////////////////////////////////	
}

void Engine::render()
{
	Start(width, height);
	Background(0, 0, 0);

	//////////////////////////////////////////////////////
	/*			RENDER PICS HERE						*/
	
	board->render();
	
	//////////////////////////////////////////////////////
	
	End();
}

void Engine::showFrames()
{
	if(oneSecTime >= 1)
	{
		printf("frames: [%d], fps: [%d]\n", frames, fps);
		
		oneSecTime = 0;
		frames = 0;
		fps = 0;
	}
	fps++;	
}


int Engine::kbhit(void)
{
	
	struct termios oldt, newt;
	 int ch;
	  int oldf;

	  tcgetattr(STDIN_FILENO, &oldt);
	  newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	 tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	  fcntl(STDIN_FILENO, F_SETFL, oldf);

	  if(ch != EOF)
	  {
		ungetc(ch, stdin);	
		isRunning = false;		
		return 1;
	  }
	  return 0;
}
