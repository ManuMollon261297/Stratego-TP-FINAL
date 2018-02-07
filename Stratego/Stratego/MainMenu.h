#pragma once
#include "mouseGameController.h"
#include "AllegroViewer.h"
#include "menuMouseController.h"
#include "MenuViewer.h"


class MainMenu
{
public:
	MainMenu(ALLEGRO_DISPLAY*, ALLEGRO_EVENT_QUEUE*);
	void Run(void);
	~MainMenu();
private:
	ALLEGRO_EVENT_QUEUE* queue;
	MenuModel* menu;
	MenuViewer* menuView;
	menuMouseController* menuControllerMouse;
	dataButtonsPos fillButtonsInfo(void);
	dataButtonsPos dataButtons;
	bool exit;
};