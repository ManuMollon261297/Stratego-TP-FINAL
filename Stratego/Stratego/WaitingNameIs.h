#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "WaitingForName.h"
#include "WaitingWhoStart.h"

class WaitingNameIs : public GenericState
{
public:
	WaitingNameIs();
	virtual ~WaitingNameIs();
	virtual GenericState* Name_is(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};