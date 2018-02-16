#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "MenuModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "Quiting.h"
#include "WaitingAttack.h"
#include "WaitingOponentDecision.h"
#include "StartingAttack.h"
#include <string>

class WaitingMove : public NetworkingState
{
public:
	WaitingMove();
	virtual NetworkingState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* MoveDone(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* AttackDone(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM);
};