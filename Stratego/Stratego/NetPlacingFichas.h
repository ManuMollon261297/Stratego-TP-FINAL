#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "WaitingMove.h"
#include "WaitingFirstMove.h"

class NetPlacingFichas : public NetworkingState
{

public:
	NetPlacingFichas();
	virtual NetworkingState* R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* EndedPlacing(NetworkingModel* p_nwm, GameModel * Gm);
};