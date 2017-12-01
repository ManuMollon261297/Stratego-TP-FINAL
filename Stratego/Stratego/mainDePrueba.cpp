#include "GameModel.h"
#include "MenuModel.h"
#include "AllegroViewer.h"
#include <iostream>

int main()
{
	GameModel engine;
	AllegroViewer viewer(500, 500,engine);
	if (viewer.isViewerInitialized)
	{
		viewer.initImagesAndFonts();
	}
	getchar();
	return 0;
}

