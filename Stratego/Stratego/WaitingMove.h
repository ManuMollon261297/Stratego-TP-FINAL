#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "Quiting.h"
#include "WaitingAttack.h"

class WaitingMove : public GenericState
{
public:

	virtual GenericState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
};