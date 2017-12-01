#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class StartingAttack : public GenericState
{
public:
	StartingAttack();
	virtual ~StartingAttack();

	virtual GenericState* Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

	virtual GenericState* Attack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};