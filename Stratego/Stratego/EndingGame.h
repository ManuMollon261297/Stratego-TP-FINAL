#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class EndingGame: public NetworkingState
{
public:

	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);  //puede ser de WaitingPlayerDecision o de WaitingNewGameResponse
};