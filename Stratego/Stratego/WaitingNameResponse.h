#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "WaitingNameIs.h"
#include "WaitingStartResponse.h"
#include "GameModel.h"
#include "gameState.h"
#include "MenuModel.h"

class WaitingNameResponse : public NetworkingState
{
public:
	WaitingNameResponse();
	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm);
};