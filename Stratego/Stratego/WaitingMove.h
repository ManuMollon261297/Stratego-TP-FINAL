#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "Quiting.h"
#include "WaitingAttack.h"

class WaitingMove : public NetworkingState
{
public:

	virtual NetworkingState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
};