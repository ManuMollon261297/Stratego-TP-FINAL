#pragma once
#include "State.h"
#include "NetworkingFuncs.h"
#include "Quiting.h"
#include "WaitingPlayerDecision.h"

class WaitingFirstMove : public NetworkingState
{
public:
	WaitingFirstMove();
	virtual NetworkingState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
};