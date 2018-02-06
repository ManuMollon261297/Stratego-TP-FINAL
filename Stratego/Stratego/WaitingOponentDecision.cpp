#include "WaitingOponentDecision.h"

WaitingOponentDecision::WaitingOponentDecision()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingOponentDecision" << std::endl;

#endif //DEBUG
}


NetworkingState* WaitingOponentDecision::Play_again(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new WaitingPlayerDecision;
	Gm->setState(GAME_OVER); //Cambio el modelo para advertir que se debe elegir si jugar de nuevo o no.
	Gm->setMessage("El oponente desea volver a jugar");
	return p_state; 
}

NetworkingState* WaitingOponentDecision::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = new Quiting;
	char pckg[1] = { ACK_HEADER };
	Gm->setState(GAME_OVER); //Hay que informarle al usuario que el otro jugador no desea seguir jugando.
	Gm->SetExit(true);
	Gm->setMessage("El oponente no desea jugar, desconectando...");
	sent = p_nwm->sendPackage(pckg, 1);
	p_nwm->Shutdown();
	return p_state;
}