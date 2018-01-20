#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "Quiting.h"
#include "WaitingAttack.h"
#include "StartingAttack.h"

class WaitingMove : public NetworkingState
{
public:

	virtual NetworkingState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* MoveDone(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* AttackDone(NetworkingModel* p_nwm, GameModel * Gm);
};