#include "State.h"
#include "NetworkingModel.h"

//Hay que agregar en todos los casos que mande un paquete de error antes del return nullptr,
//menos quit y error
//Hay que cerrrar la comunicacion despues de enviar el paquete de error.

GenericState:: ~GenericState()
{

}

GenericState* GenericState::Play_again(GenericEvent& ev,  NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::Name(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::Name_is(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::I_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::You_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::R_u_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::I_am_ready(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::You_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::Ack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::Game_over(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::Move(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::You_won(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

GenericState* GenericState::Attack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}


GenericState* GenericState::Quit(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ACK_HEADER };
	p_nwm->sendPackage(message, 1);
	Gm->setState(GAME_OVER);
	return nullptr;
}

GenericState* GenericState::Error(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}