#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "WaitingNameIs.h"
#include "WaitingStartResponse.h"
#include "GameModel.h"

class WaitingNameResponse : public NetworkingState
{
public:

	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};