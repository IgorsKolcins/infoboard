#include "WgKpnference.h"



WgKpnference::WgKpnference(int AscrWidth, int AscrHeight, int Ax, int Ay, wgMode Amode) : 
	WgBackground(AscrWidth, AscrHeight, Ax, Ay, Amode) 
{
	saraksts = new Picture("resources/saraksts.png");
	setUpdTime(6000);
	setColor(clGreen);
	update();	
}

void WgKpnference::update(){
	/*sprintf(nr[1], "%d) Viduslaiku krāsu atjaunošana,izmantojot dabiskās vielas un materiālus", 1);
	sprintf(nr[2], "%d) Dažādu krāsu patinas pārklājumu iegūšana uz vara plāksnēm", 2);
	sprintf(nr[3], "%d) Dabiskā un mākslīgi iegūtā dzintara īpašību salīdzinājums", 3);
	sprintf(nr[4], "%d) Organiskās un sintētiskās līmes, priekšrocības un trūkumi", 4);
	sprintf(nr[5], "%d) Asinsspiediena un pulsa izmaiņas humanitāro un eksakto priekšmetu stundu ietekmē", 5);
	sprintf(nr[6], "%d) Ķermeņa trajektorijas digitāla rekonstruēšana ", 6);
	sprintf(nr[7], "%d) Sfēriskais robots", 7);
	sprintf(nr[8], "%d) Fitoncīdi kā tomātu fitoftorozes apkarošanas līdzeklis", 8);
	sprintf(nr[9], "%d) ZnO un ZnO/Ag nanostruktūru iegūšana, to antibakteriālās īpašības", 9);
	sprintf(nr[10], "%d) ZnO nanostruktūru hidrofobas un hidrofilas īpašības", 10);
	sprintf(nr[11], "%d) Research of chaotic behavior in Chua`s electronic circuit", 11);
	sprintf(nr[12], "%d) Diskriminējošais metāla detaktors", 12);
	sprintf(nr[13], "%d) Video apstrāde ar Ulead Video Studio", 13);
	sprintf(nr[14], "%d) Video un audio analogsignāla digitalizācija", 14);
	sprintf(nr[15], "%d) Vadības sistēma \"SMART RTU\"", 15);
	sprintf(nr[16], "%d) Sistēmas \"SMART RTU\" vizuāla aplikācija", 16);
	sprintf(nr[17], "%d) Sistēmas \"SMART RTU\" elektroiekārtu kontrole", 17);
	sprintf(nr[18], "%d) PARRALAX", 18);
	sprintf(nr[19], "%d) Metāla detektors \"Pirats\"", 19);
	sprintf(nr[20], "%d) Application development for SIRS epidemic model analysis", 20);
	sprintf(nr[21], "%d) Sistemas \"SMART RTU\" šriftu apstrade", 21);*/
	
	
}

void WgKpnference::render1(){
	text->SetColour(255,255,255);
	text->SetSize(oneGridStep.vertical/2);
	text->TextMid("Konferences saraksts", posx+ oneGridStep.horizontal + (oneGridStep.horizontal/2),
		posy + (oneGridStep.vertical/4));
}

void WgKpnference::render(){
	WgBackground::render();
	this->render1();
	
	saraksts->render(565, 23, 0.91, 0.92, 0, 0, 0);
}
