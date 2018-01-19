#include "WaitingNewGameResponse.h"

NetworkingState* WaitingNewGameResponse::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state= new NetPlacingFichas;
	p_nwm->setServer(CLIENT);
	Gm->setState(PLACING_FICHAS);
	p_nwm->SetServerFinishedPlacing(true);
	Gm->setRed(!(Gm->getRed()));
		//Falta una funcion de Game Model que prepare todo para volver a jugar.
	return p_state;
}

NetworkingState* WaitingNewGameResponse::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new Quiting;
	Gm->SetExit(true);
}