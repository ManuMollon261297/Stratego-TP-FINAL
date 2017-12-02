#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "WaitingForName.h"
#include "WaitingWhoStart.h"

class WaitingNameIs : public NetworkingState
{
public:
	virtual NetworkingState* Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};