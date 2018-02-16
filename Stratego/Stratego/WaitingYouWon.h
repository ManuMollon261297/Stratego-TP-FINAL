#pragma once
#include "State.h"
#include "WaitingPlayerDecision.h"
#include "NetworkingFuncs.h"

class WaitingYouWon : public NetworkingState
{
public:
	WaitingYouWon(void);
	virtual NetworkingState* You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM);
};