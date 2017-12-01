#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "WaitingNameIs.h"
#include "WaitingStartResponse.h"
#include "GameModel.h"

class WaitingNameResponse : public GenericState
{
public:

	virtual GenericState* Ack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};