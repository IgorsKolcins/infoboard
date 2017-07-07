/*WgAds
 * Visual widget.
 * 	Show some ads and notifications.
 * 
 */
#pragma once
#include "WgBackground.h"

class WgAds : public WgBackground
{
private:
	char ads[3000];
	
public:
	WgAds(int AscrWidth, int AscrHeight, int AposX, int AposY, wgMode Amode);
	~WgAds();
	
	void update();
	void render();
};
