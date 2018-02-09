#pragma once
#include <vector>
#include "GenericController.h"
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
	vector<GenericController*> v_contr;
	dataButtonsPos fillButtonsInfo(void);
	dataButtonsPos dataButtons;
	bool exit;
};