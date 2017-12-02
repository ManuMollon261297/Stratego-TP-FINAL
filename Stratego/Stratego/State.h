#pragma once

#include "Event.h"
#include "NetWorkingEvent.h"
#include "MouseEvent.h"
#include "NetworkingModel.h"
#include "GameModel.h"

enum gameTypeState { NOT_CONNECTED, CONNECTING_TO_CLIENT, CONNECTING_TO_SERVER, WAITING_NAME, WAITING_NAME_IS,
				WAITING_NAME_RESPONSE, WAITING_WHO_STARTS, WAITING_START_RESPONSE, PLACING_FICHAS,
				WAITING_READINESS, WAITING_MOVE, WAITING_ATTACK, WAITING_NEW_GAME, WAITING_PLAYER_DECISION,
				STARTING_ATTACK, WAITING_NEW_GAME_RESPONSE, WAITING_OPONENT_DECISION ,ENDING_GAME, QUITING};

//Estan los headers de:
//WAITING_NAME, WAITING_NAME_IS, WAITING_NAME_RESPONSE, WAITING_WHO_STARTS, WAITING_START_RESPONSE,
//WAITING_MOVE, WAITING_ATTACK, STARTING_ATTACK, WAITING_PLAYER_DECISION, WAITING_NEW_GAME_RESPONSE,
//ENDING_GAME, QUITING, WAITING_OPONENT_DECISION

//Faltan los headers de:
//NOT_CONNECTED, CONNECTING_TO_CLIENT, CONNECTING_TO_SERVER,
//WAITING_READINESS, WAITING_NEW_GAME


class NetworkingState
{
public:
	virtual ~NetworkingState();
	virtual NetworkingState* Play_again(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Error(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* Quit(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual NetworkingState* ButtonPressed(MouseEvent&, NetworkingModel* p_nwm, GameModel * Gm);
};