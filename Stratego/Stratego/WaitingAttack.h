#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "Quiting.h"
#include "WaitingPlayerDecision.h"
#include "WaitingMove.h"
#include "GameModel.h"

class WaitingAttack : public GenericState
{
public:

	virtual GenericState* Attack(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* You_won(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};