#include "board.h"


Board::Board()
{
	cleanWidgets();
	
	float c = 5.4;
	float a = 6/c;
	float b = 10/a;
	int e = 258;
	
	WgClock *buf;
	buf = new WgClock(1280, 720, 2, 5, md1x3);
	buf->setGrid(c,b);	
	buf->setXY(e, 485);
	addWidget(buf);
	
	WgCalendar *buf2;
	buf2 = new WgCalendar(1280, 720, 1, 5, md1x3);
	buf2->setGrid(c,b);	
	buf2->setXY(e,202);
	addWidget(buf2);
	
	WgWeather *buf3;
	buf3 = new WgWeather(1280, 720, 3, 5, md1x1);
	buf3->setGrid(c,b);	
	buf3->setXY(e, 610);
	addWidget(buf3);
	
	
	
	WgKpnference *buf4;
	buf4 = new WgKpnference(1280, 720, 3, 5, md2x8);
	buf4->update();
	//buf4->setGrid(c,b);	
	buf4->setXY(550, 618);
	addWidget(buf4);

	
	first = -1;
	next = -1;
	
	
	bckgrnd = new ScrBackground(1280, 720);
	logo = new Picture("resources/logo.png");
}

Board::~Board() 
{
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i]) delete widgets[i];
	}
	
	
	delete bckgrnd;
	delete logo;
}

void Board::update()
{
	// update data (check weather, check time and blah blah blah ... )
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i]) widgets[i]->update();
	}	
}

void Board::render()
{
	// just drowing functions!!!
	// p.s do not change name of function (drawClock, drawWeather ... name it just render();
	

	bckgrnd->render();
	logo->render(20,560,0.6,0.6,0,0,0);
	
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i])
		{ 
			widgets[i]->render();
		}
	}
}


void Board::addWidget(IWidget *widget)
{
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i] == NULL)
		{ 
			widgets[i] = widget;
			widgets[i]->setId(i);
			return;
		}
	}
}

void Board::cleanWidgets()
{
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		//if(widgets[i]) delete widgets[i];
		widgets[i] = NULL;
	}
}

IWidget **Board::getWidgets()
{
	return widgets;
	
}

IWidget *Board::findFirst()
{
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i])
		{
			first = i;
			next = i + 1;
			return widgets[i];
		}
	}
	return NULL;
}

IWidget *Board::findNext()
{
	if(first != -1 && next != -1 && next < WIDGETS_COUNT)
	{
		for(int i = next; i < WIDGETS_COUNT; i++)
		{
			if(widgets[i]) 
			{
				if(next + 1 < WIDGETS_COUNT) next = i + 1;
				else return NULL;
				return widgets[i];
			}
		}
		return NULL;
	}
	return NULL;
}

int Board::countWidgets()
{
	int wCount = 0;
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i])
		{
			wCount++;
		}
	}
	return wCount;
}





















