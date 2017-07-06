#include "board.h"
#include "CPicturesStorage.h"

#include "widgets/WgClock.h"
#include "widgets/WgCalendar.h"
#include "widgets/WgForecast.h"

Board::Board()
{
	cleanWidgets();

	addWidget(new WgForecast(1280, 720, 2, 7, md1x1));
	addWidget(new WgClock(1280, 720, 3, 7, md1x3));
	addWidget(new WgCalendar(1280, 720, 4, 7, md1x3));
	
	first = -1;
	next = -1;
}

Board::~Board() 
{
	for(int i = 0; i < WIDGETS_COUNT; i++)
	{
		if(widgets[i]) delete widgets[i];
	}
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
	PicStorage->ScreenBackgroud->render(0,0);
	PicStorage->Logo->render(20,560,0.6,0.6,0,0,0);
	
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





















