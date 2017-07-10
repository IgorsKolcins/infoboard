/*WgAds
 * Visual widget.
 * 	Show some ads and notifications.
 * 
 */
#pragma once
#include "WgBackground.h"

#include "iostream"
using namespace std;

class WgAds : public WgBackground
{
private:
	char ads[3000];
	char *adsPeace[50];
	
	
	int lineCount;
	
	bool readFile(char *text);
	bool isAds;
	
public:
	WgAds(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
	~WgAds();
	
	int Separate( char * Src, char ** Dst = NULL );
	
	void update();
	void render();
};
