#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "WaitingNameResponse.h"
#include "GameModel.h"
#include <iostream>

class WaitingName : public GenericState
{
public:
	WaitingName();
	virtual ~WaitingName();
	virtual GenericState* Name(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	//virtual GenericState* Connection_succes(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};