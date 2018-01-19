#include "WaitingOponentDecision.h"

NetworkingState* WaitingOponentDecision::Play_again(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new WaitingPlayerDecision;
	Gm->setState(GAME_OVER); //Cambio el modelo para advertir que se debe elegir si jugar de nuevo o no.
	return p_state; 
}

NetworkingState* WaitingOponentDecision::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new Quiting;
	char pckg[1] = { ACK_HEADER };
	Gm->setState(GAME_OVER); //Hay que informarle al otro usuario que el otor jugador no desea seguir jugando.
	Gm->SetExit(true);
	p_nwm->sendPackage(pckg, 1);
	return p_state;
}