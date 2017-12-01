#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class WaitingOponentDecision : public GenericState
{
public:
	WaitingOponentDecision();
	virtual ~WaitingOponentDecision();

	virtual GenericState* Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

	virtual GenericState* R_u_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};