#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "NetPlacingFichas.h"
#include "GameModel.h"
#include "gameState.h"

class WaitingStartResponse : public NetworkingState
{
public:
	WaitingStartResponse();
	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm);
};