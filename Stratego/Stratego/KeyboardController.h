#pragma once

#include "MenuModel.h"
#include "KeyboardEvent.h"
#include <allegro5\allegro.h>

class KeyboardController
{
public:
	KeyboardController(MenuModel * mm, ALLEGRO_EVENT_QUEUE * queue_, unsigned int maxIp = 21, unsigned int maxName = 20);
	~KeyboardController();
	void takeEvent(GenericEvent * genEv);

private:

	bool mayus;

	bool validateAdd(void);
	bool validateSub(void);

	MenuModel * pMenuModel;

	unsigned int IpMax;
	unsigned int NameMax;

	unsigned int IpCount;
	unsigned int NameCount;
	bool initOk;
	ALLEGRO_EVENT_QUEUE * queue;
};