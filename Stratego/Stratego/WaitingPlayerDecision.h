#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class WaitingPlayerDecision : public GenericState
{
public:
	WaitingPlayerDecision();
	virtual ~WaitingPlayerDecision();

	virtual GenericState* Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

	virtual GenericState* You_won(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);		//Puede ser desde un WaitingMove o desde un WaitingAttack
};