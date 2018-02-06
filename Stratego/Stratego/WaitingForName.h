#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "WaitingNameResponse.h"
#include "GameModel.h"
#include "gameState.h"
#include <iostream>

class WaitingName : public NetworkingState
{
public:
	WaitingForName();
	virtual NetworkingState* Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm);
};