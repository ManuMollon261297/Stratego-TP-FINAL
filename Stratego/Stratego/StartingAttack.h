#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "Quiting.h"
#include "WaitingMove.h"

class StartingAttack : public GenericState
{
public:

	virtual GenericState* Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};