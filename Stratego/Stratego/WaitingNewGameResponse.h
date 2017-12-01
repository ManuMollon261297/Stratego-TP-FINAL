#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class WaitingNewGameResponse : public GenericState
{
public:
	WaitingNewGameResponse();
	virtual ~WaitingNewGameResponse();

	virtual GenericState* Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

	virtual GenericState* Play_again(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};