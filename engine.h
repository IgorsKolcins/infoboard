//  basic
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

//  our classes
#include "board.h"
#include "lib/Picture.h"



//  includes to kbhit function
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define FRAMES_PER_SECOND 25.0


class Engine
{
private:

	int width, height;
	double frameCap;
	double firstTime;
	double lastTime;
	double passedTime;
	double unprocessedTime;
	double oneSecTime;
	double updateTime;
	int frames;
	int fps;
	bool isRunning;
	
	Board *board;
	IWidget *w;
	
	
	void run();
	void update();
	void render();
	void showFrames();
	int kbhit(void);
	
public:
	
	
	Engine(int width, int height);
	~Engine();
	void start();

};
