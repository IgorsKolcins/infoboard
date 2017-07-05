#include "widgets/WgClock.h"
#include "widgets/IWidget.h"

class Board
{
private:

	const static int WIDGETS_COUNT = 10;
	IWidget *widgets[WIDGETS_COUNT];
	int first;
	int next;
    void cleanWidgets();
	
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
