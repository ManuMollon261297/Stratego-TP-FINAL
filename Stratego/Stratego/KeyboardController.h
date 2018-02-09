#pragma once

#include "GenericController.h"
#include "MenuModel.h"
#include "KeyboardEvent.h"
#include <allegro5\allegro.h>

class KeyboardController : public GenericController
{
public:
	KeyboardController(MenuModel * mm, unsigned int maxIp = 21, unsigned int maxName = 8);
	~KeyboardController();
	virtual void  dispatch(GenericEvent& genEv);

private:
	bool validateAdd(void);
	bool validateSub(void);

	MenuModel * pMenuModel;

	bool initOk;
	bool bloqMayus;

	unsigned int IpMax;
	unsigned int NameMax;
	unsigned int IpCount;
	unsigned int NameCount;
};
