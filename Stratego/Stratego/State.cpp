#include "State.h"
#include "NetworkingModel.h"



NetworkingState:: ~NetworkingState()
{

}

NetworkingState* NetworkingState::Play_again(NetWorkingEvent& ev,  NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}


NetworkingState* NetworkingState::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}


NetworkingState* NetworkingState::Quit(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ACK_HEADER };
	p_nwm->sendPackage(message, 1);
	Gm->SetExit(true);
	p_nwm->Shutdown();
	Gm->setMessage("Comm error, quiting...");
	return nullptr;
}

NetworkingState* NetworkingState::Error(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	p_nwm->Shutdown();
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	Gm->setMessage("Comm error, quiting...");
	return nullptr;
}

NetworkingState* NetworkingState::UnknownHeader(NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::EndedPlacing(NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}
NetworkingState* NetworkingState::SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}
NetworkingState* NetworkingState::SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}
NetworkingState* NetworkingState::MoveDone(NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}
NetworkingState* NetworkingState::AttackDone(NetworkingModel* p_nwm, GameModel * Gm)
{
	ErrorRoutine(p_nwm, Gm);
	return nullptr;
}

NetworkingState* NetworkingState::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
{
	return nullptr; //el caso base no hace nada.
}


void NetworkingState::ErrorRoutine(NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1] = { ERROR_HEADER };
	p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.
	Gm->SetExit(true);
	Gm->setMessage("Comm error, quiting...");

	p_nwm->Shutdown();
}