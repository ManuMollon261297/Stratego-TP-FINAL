#pragma once

#include "Event.h"
#include "NetWorkingEvent.h"
#include "MouseEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"
#include "gameState.h"

#define DEBUG



class NetworkingState
{
public:
	virtual ~NetworkingState();
	//Rutinas vinculadas a paquetes recibidos
	virtual NetworkingState* Play_again(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Error(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Quit(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* UnknownHeader(NetworkingModel* p_nwm, GameModel * Gm);

	//Rutinas vinculadas al input del usuario
	virtual NetworkingState* EndedPlacing(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* MoveDone(NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* AttackDone(NetworkingModel* p_nwm, GameModel * Gm);

	//Rutina del timer
	virtual NetworkingState* OnTimer(NetworkingModel* p_nwm, GameModel * Gm);


protected:
	void ErrorRoutine(NetworkingModel* p_nwm, GameModel * Gm);
};