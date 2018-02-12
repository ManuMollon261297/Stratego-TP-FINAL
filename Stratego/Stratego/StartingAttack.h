#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "MenuModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "Quiting.h"
#include "WaitingMove.h"
#include "WaitingOponentDecision.h"
#include "WaitingYouWon.h"

class StartingAttack : public NetworkingState
{
public:
	StartingAttack();
	virtual NetworkingState* Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM);
};