#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "Quiting.h"
#include "WaitingPlayerDecision.h"

class WaitingOponentDecision : public NetworkingState
{
public:
	WaitingOponentDecision();
	virtual NetworkingState* Play_again(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};