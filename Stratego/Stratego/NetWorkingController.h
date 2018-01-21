#pragma once

#include "NetWorkingEvent.h"
#include "State.h"
#include "NetworkingModel.h"
#include <time.h>
#include <fstream>
#include "NetPlacingFichas.h"
#include "Quiting.h"
#include "StartingAttack.h"
#include "WaitingAttack.h"
#include "WaitingForName.h"
#include "WaitingMove.h"
#include "WaitingNameIs.h"
#include "WaitingNameResponse.h"
#include "WaitingNewGameResponse.h"
#include "WaitingOponentDecision.h"
#include "WaitingPlayerDecision.h"
#include "WaitingStartResponse.h"
#include "WaitingWhoStart.h"
#include "GameModel.h"
#include "gameState.h"

#define MAX_IP_LENGTH 45

class NetWorkingController
{
public:
	NetWorkingController(GameModel* p2GameModel);
	~NetWorkingController();
	void dispatch(GenericEvent& newEvent);

private:
	NetworkingState * actualState;
	NetworkingState * proxState;
	NetworkingModel * NWM;     
	GameModel * Gm;
	char ip[MAX_IP_LENGTH+1]; //ip del otro jugador
};