#include "widgets/WgClock.h"
#include "widgets/WgCalendar.h"
#include "widgets/ScrBackground.h"
#include "widgets/IWidget.h"
#include "widgets/WgWeather.h"
#include "widgets/WgKpnference.h"


class Board
{
private:

	const static int WIDGETS_COUNT = 10;
	IWidget *widgets[WIDGETS_COUNT];
	ScrBackground *bckgrnd;
	int first;
	int next;
    void cleanWidgets();
	Picture *logo;
	
	
public:	

	Board();
	~Board();
	void update();
	void render();
	void addWidget(IWidget *widget);
	IWidget **getWidgets();
	IWidget *findFirst();
	IWidget *findNext();
	
	
	int getMaxWidgetsCount() { return WIDGETS_COUNT; }
	int countWidgets();
	
};
