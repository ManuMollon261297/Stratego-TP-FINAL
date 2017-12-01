#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "WaitingMove.h"

class NetPlacingFichas : public GenericState
{

public:

	virtual GenericState* R_u_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* I_am_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};