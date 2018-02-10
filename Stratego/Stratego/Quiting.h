#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "MenuModel.h"
#include "GameModel.h"
#include "gameState.h"

class Quiting : public NetworkingState
{
public:
	Quiting();
	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM);
};