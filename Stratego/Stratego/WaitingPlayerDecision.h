#pragma once

#include "State.h"
#include "NetWorkingEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "gameState.h"
#include "WaitingNewGameResponse.h"
#include "NetPlacingFichas.h"

class WaitingPlayerDecision : public NetworkingState
{
public:
	WaitingPlayerDecision();
	virtual NetworkingState* SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm);
};