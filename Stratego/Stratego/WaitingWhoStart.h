#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "NetPlacingFichas.h"
#include "GameModel.h"
#include "gameState.h"

class WaitingWhoStart : public NetworkingState
{
public:
	WaitingWhoStart(void);
	virtual NetworkingState* I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

};