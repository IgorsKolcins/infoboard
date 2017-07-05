#include "ScrBackground.h"


ScrBackground::ScrBackground(){
	image = new Picture("resources/Background.jpg");
	sclx = 1280.0/image->getWidth();
	scly = 720.0/image->getHeight();
}

ScrBackground::ScrBackground(int w, int h){
	image = new Picture("resources/Background.jpg");
	sclx = (float)w/image->getWidth();
	scly = (float)h/image->getHeight();
}

ScrBackground::~ScrBackground(){
	delete image;
}

void ScrBackground::render(){
	image->render(0, 0, sclx, scly, 0,0,0);
	
}

void ScrBackground::update(){
	
}
 
