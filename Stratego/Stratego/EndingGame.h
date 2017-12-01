#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class EndingGame: public GenericState
{
public:
	EndingGame();
	virtual ~EndingGame();

	virtual GenericState* Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

	virtual GenericState* Ack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);  //puede ser de WaitingPlayerDecision o de WaitingNewGameResponse
};