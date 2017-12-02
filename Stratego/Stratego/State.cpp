#include "State.h"
#include "NetworkingModel.h"

//Hay que agregar en todos los casos que mande un paquete de error antes del return nullptr,
//menos quit y error
//Hay que cerrrar la comunicacion despues de enviar el paquete de error.

NetworkingState:: ~NetworkingState()
{

}

NetworkingState* NetworkingState::Play_again(NetWorkingEvent& ev,  NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}


NetworkingState* NetworkingState::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}


NetworkingState* NetworkingState::Quit(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ACK_HEADER };
	p_nwm->sendPackage(message, 1);
	Gm->setState(GAME_OVER);
	return nullptr;
}

NetworkingState* NetworkingState::Error(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::ButtonPressed(MouseEvent&, NetworkingModel* p_nwm, GameModel * Gm)
{
	return nullptr; //En el caso general si llega un evento del mouse o ignora.
}