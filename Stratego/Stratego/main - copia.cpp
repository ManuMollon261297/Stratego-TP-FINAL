#include "GameModel.h"
#include "AllegroViewer.h"

int main()
{
	pos inicial(6, 5);
	pos final(6,0);
	GameModel engine;
	engine.setRed(true);
	AllegroViewer viewer(720, 1080, engine, RED);
	viewer.initImagesAndFonts();
	for (int i =6;i<10;i++)
	{
		for (int j =0;j<10;j++)
		{
			pos curr(i, j);
			engine.setFicha(rank::SCOUT, curr);
		}
	}
	viewer.drawBackground();
	viewer.drawBattlefield();
	viewer.drawCemetery();
	al_flip_display();
	viewer.moveToken(inicial, final);
//	al_flip_display();
	getchar();
	return 0;
}
/*
void drawMessage();
void drawRemainingTime();
*/