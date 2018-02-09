#pragma once
#include "mouseGameController.h"
#include "AllegroViewer.h"
#include "menuMouseController.h"
#include "MenuViewer.h"
#include "KeyboardController.h"
#include "KeyboardEvent.h"


class MainMenu
{
public:
	MainMenu(ALLEGRO_DISPLAY*, ALLEGRO_EVENT_QUEUE*);
	void Run(void);
	~MainMenu();
private:
	ALLEGRO_EVENT_QUEUE* queue;
	MenuModel* menu;
	MenuViewer* menu_viewer;
	menuMouseController* menuControllerMouse;
	KeyboardController* KeyController;
	dataButtonsPos fillButtonsInfo(void);
	dataButtonsPos dataButtons;
	bool exit;
};