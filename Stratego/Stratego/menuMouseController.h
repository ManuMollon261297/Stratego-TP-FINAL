#pragma once

#include "MenuModel.h"
#include "mouseMenuEvent.h"


class menuMouseController
{
public:
	menuMouseController(MenuModel * p2menuModel_, dataButtonsPos & dataButtonsPos_);
	~menuMouseController();
	int shape(int x, int y);

	void refreshButtons(void);

	virtual void dispatch(GenericEvent & menuEvMouse);

private:
	MenuModel * p2menuModel;

	void * estadoModel_;

	dataButtonsPos dataButtons;

	int state;

};

