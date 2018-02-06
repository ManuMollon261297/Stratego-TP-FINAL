#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "Quiting.h"
#include "NetPlacingFichas.h"

class WaitingNewGameResponse : public NetworkingState
{
public:
	WaitingNewGameResponse();
	virtual NetworkingState* R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};