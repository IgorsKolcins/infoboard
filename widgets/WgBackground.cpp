#include "WgBackground.h"

//TFont text("lib/TFont/ArialBold.ttf");
//Picture a("resources/constructor/sTop.png");

WgBackground::WgBackground(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode){
	
	setScr(AscrWidth, AscrHeight);
    setPos(Ax, Ay);
    setMode(Amode);
    setColor(clBlue);
	setUpdTime(UPDATE_TIME_SEK);

	shadows.top=true; 
	shadows.bot=true;
	shadows.left=true; 
	shadows.right=true;
	
	oneGridStep.horizontal = scrWidth/6;
	oneGridStep.vertical = scrHeight/10;

	/*shadowsPictures.t = new Picture("resources/constructor/sTop.png");
	shadowsPictures.lt = new Picture("resources/constructor/sLeftTop.png");
	shadowsPictures.rt = new Picture("resources/constructor/sRightTop.png");
	shadowsPictures.b = new Picture("resources/constructor/sBot.png");
	shadowsPictures.lb = new Picture("resources/constructor/sLeftBot.png");
	shadowsPictures.rb = new Picture("resources/constructor/sRightBot.png");
	shadowsPictures.l = new Picture("resources/constructor/sLeft.png");
	shadowsPictures.r = new Picture("resources/constructor/sRight.png");*/
	
	text = new TFont("lib/TFont/ArialBold.ttf");
}



WgBackground::~WgBackground(){
	/*delete shadowsPictures.t;
	delete shadowsPictures.b;
	delete shadowsPictures.l;
	delete shadowsPictures.r;
	delete shadowsPictures.lt;
	delete shadowsPictures.rb;
	delete shadowsPictures.lb;
	delete shadowsPictures.rt;*/
	delete text;
}

void WgBackground::setFillColor(wgColor c){
	if (c==0) Fill(255,255,255,1);
	else if (c==1) Fill(0,121,194,1);
	else if (c==2) Fill(37,196,166,1);
	else if (c==3) Fill(139,209,93,1);
	else if (c==4) Fill(0,185,241,1);
	else if (c==5) Fill(139,91,164,1);
	else if (c==6) Fill(201,208,34,1);
	else if (c==7) Fill(240,115,30,1);
	else if (c==8) Fill(183,46,145,1);
	else if (c==9) Fill(255,200,50,1);	
}
void WgBackground::setTextColor(wgColor c){
if (c==1) text->SetColour(0,121,194);
	else if (c==2) text->SetColour(37,196,166);
	else if (c==3) text->SetColour(139,209,93);
	else if (c==5) text->SetColour(139,91,164);
	else if (c==6) text->SetColour(201,208,34);
	else if (c==7) text->SetColour(240,115,30);
	else if (c==8) text->SetColour(183,46,145);
	else if (c==9) text->SetColour(255,200,50);	
}

void WgBackground::render(){

	switch (mode){
		case md1x1: {sizeX = 1; sizeY = 1; break;}
		case md1x2: {sizeX = 1; sizeY = 2; break;}
		case md1x3: {sizeX = 1; sizeY = 3; break;}
		case md2x8: {sizeX = 3; sizeY = 9; break;}
	}

	

	if (grid){
		posx = oneGridStep.horizontal*x;
		posy = oneGridStep.vertical*y;}
	/*else {
		posx = x;
		posy = y;}*/
	

	for (int i=0; i<sizeX; i++){
		for (int j=0; j<sizeY; j++){
			if (j==0) setFillColor(color);
			else setFillColor(clWhite);
			Rect(posx+oneGridStep.horizontal*i,
				 posy-oneGridStep.vertical*j,
				 oneGridStep.horizontal, oneGridStep.vertical);
		}
	}

	int w = oneGridStep.horizontal * sizeX;
	int h = oneGridStep.vertical *sizeY;
	int Y = posy - oneGridStep.vertical*(sizeY-1);
	
	/*if (shadows.top){ 
		for (int i=0; i<w; i++){
			shadowsPictures.t->render(posx+i, Y+h, 1, 1, 0,0,0);
		}
		if (left){
			shadowsPictures.lt->render(posx-9, Y+h, 1, 1, 0,0,0); 
		}
		if (right){
			shadowsPictures.rt->render(posx+w, Y+h, 1, 1, 0,0,0); 
		}
	}
	if (shadows.bot) {
		for (int i=0; i<w; i++){
			shadowsPictures.b->render(posx+i, Y-9, 1, 1, 0,0,0); 
		}
		if (left){
			shadowsPictures.lb->render(posx-9, Y-9, 1, 1, 0,0,0); 
		}
		if (right){
			shadowsPictures.rb->render(posx+w, Y-9, 1, 1, 0,0,0); 
		}
		
	}
	if (shadows.left) {
		for (int i=0; i<h; i++){
			shadowsPictures.l->render(posx-9, Y+i, 1, 1, 0,0,0); 
		}
		
	}
	if (shadows.right) {
		for (int i=0; i<h; i++){
			shadowsPictures.r->render(posx+w, Y+i, 1, 1, 0,0,0); 
		}
	}*/
}
