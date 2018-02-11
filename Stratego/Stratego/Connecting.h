#pragma once
#include "State.h"
#include "WaitingForName.h"
#include "WaitingNameIs.h"

class Connecting : public NetworkingState
{
public:
	Connecting();
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM);
	virtual NetworkingState* Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};