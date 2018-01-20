#pragma once

#include "State.h"
#include "NetworkingFuncs.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "Quiting.h"
#include "WaitingPlayerDecision.h"
#include "WaitingMove.h"
#include "GameModel.h"

class WaitingAttack : public NetworkingState
{
public:

	virtual NetworkingState* Attack(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};