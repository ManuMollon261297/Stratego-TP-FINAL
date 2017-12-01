#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "PlacingFichas.h"
#include "GameModel.h"

class WaitingWhoStart : public GenericState
{
public:
	virtual GenericState* I_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* You_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

};