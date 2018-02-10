#include "WaitingNewGameResponse.h"

WaitingNewGameResponse::WaitingNewGameResponse()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingNewGameResponse" << std::endl;

#endif //DEBUG
}


NetworkingState* WaitingNewGameResponse::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state= new NetPlacingFichas;
	p_nwm->setServer(CLIENT);
	Gm->setState(PLACING_FICHAS);
	p_nwm->SetServerFinishedPlacing(true);
	Gm->reset();//Prepara todo para una partida nueva.
	return p_state;
}

NetworkingState* WaitingNewGameResponse::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1] = { ACK_HEADER };
	NetworkingState* p_state = new Quiting;
	Gm->SetExit(true);
	Gm->setMessage("Oponent exit, quiting...");
	p_nwm->sendPackage(pckg, 1);
	p_nwm->Shutdown();
	return p_state;
}