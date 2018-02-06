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
	Gm->SetExit(true);
	return nullptr;
}

NetworkingState* NetworkingState::Error(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	p_nwm->Shutdown();
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	Gm->setMessage("Error de comunicacion, cerrando...");
	return nullptr;
}

NetworkingState* NetworkingState::EndedPlacing(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);

	sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.

	return nullptr;
}
NetworkingState* NetworkingState::SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);

	sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.


	return nullptr;
}
NetworkingState* NetworkingState::SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	
	sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.
	

	return nullptr;
}
NetworkingState* NetworkingState::MoveDone(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.

	return nullptr;
}
NetworkingState* NetworkingState::AttackDone(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	
	sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.

	return nullptr;
}

NetworkingState* NetworkingState::OnTimer(NetworkingModel* p_nwm, GameModel * Gm)
{
	return nullptr; //el caso base no hace nada.
}
