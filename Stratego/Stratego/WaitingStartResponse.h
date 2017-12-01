#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "PlacingFichas.h"
#include "GameModel.h"

class WaitingStartResponse : public GenericState
{
public:

	virtual GenericState* Ack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};