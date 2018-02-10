#pragma once

#include "GenericController.h"
#include "NetWorkingEvent.h"
#include "State.h"
#include "Connecting.h"
#include "NetworkingModel.h"
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
#include "MenuModel.h"



class NetWorkingController: public GenericController
{
public:
	NetWorkingController(GameModel* p2GameModel, NetworkingModel* p2NetModel);
	~NetWorkingController();
	virtual void dispatch(GenericEvent& newEvent);
	void AddMainMenu(MenuModel*);
	serverStatus GetServer(void)const;

private:
	NetworkingState * actualState;
	NetworkingState * proxState;
	NetworkingModel * NWM;     
	GameModel * Gm;
	MenuModel * MM;

};