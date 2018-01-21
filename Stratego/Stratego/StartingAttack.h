#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "Quiting.h"
#include "WaitingMove.h"
#include "WaitingOponentDecision.h"

class StartingAttack : public NetworkingState
{
public:

	virtual NetworkingState* Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};