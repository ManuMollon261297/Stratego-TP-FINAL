#pragma once

#include "NetWorkingEvent.h"
#include "State.h"
#include "NetworkingModel.h"
#include "EndingGame.h"
#include <time.h>
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


class NetWorkingController
{
public:
	NetWorkingController(GameModel* p2GameModel);
	~NetWorkingController();
	void dispatch(GenericEvent& newEvent);

private:
	GenericState * actualState;
	GenericState * proxState;
	NetworkingModel * NWM;     //decidir si es un puntero o contiene al objeto en si
	GameModel * Gm;
	char * ip; //ip del otro jugador
};