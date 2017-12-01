#pragma once

#include "Event.h"
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


class GenericState
{
public:
	virtual ~GenericState();
	virtual GenericState* Play_again(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Name(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Name_is(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* I_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* You_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* R_u_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* I_am_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* You_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Ack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Game_over(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Move(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* You_won(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Attack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);

	//verify 

	virtual GenericState* Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
	virtual GenericState* Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm);
};