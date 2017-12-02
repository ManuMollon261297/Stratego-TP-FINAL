#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

class WaitingPlayerDecision : public NetworkingState
{
public:
	virtual NetworkingState* You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);		//Puede ser desde un WaitingMove o desde un WaitingAttack
};