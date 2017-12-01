#include "GameModel.h"
#include "MenuModel.h"
#include "AllegroViewer.h"
#include <iostream>

int main()
{
	AllegroViewer viewer(500, 500);
	if (viewer.isViewerInitialized)
	{
		viewer.initImagesAndFonts();
	}
	getchar();
	return 0;
}

