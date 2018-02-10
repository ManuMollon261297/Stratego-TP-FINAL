#pragma once
#include <vector>
#include "EventGenerator.h"
#include "GenericController.h"
#include "mouseGameController.h"
#include "AllegroViewer.h"
#include "menuMouseController.h"
#include "MenuViewer.h"
#include "KeyboardController.h"
#include "KeyboardEvent.h"
#include "NetWorkingController.h"


class MainMenu
{
public:
	MainMenu(ALLEGRO_DISPLAY*, ALLEGRO_EVENT_QUEUE*, NetWorkingController*, EventGenerator*);
	bool Run(void);
	~MainMenu();
private:
	ALLEGRO_EVENT_QUEUE* queue;
	MenuModel* menu;
	NetWorkingController* p_nw;
	EventGenerator* p_Ev_gen;

	vector<GenericController*> v_contr;
	dataButtonsPos fillButtonsInfo(void);
	dataButtonsPos dataButtons;
	bool connected;
};