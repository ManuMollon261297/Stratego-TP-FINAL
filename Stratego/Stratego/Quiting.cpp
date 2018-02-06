#include "Quiting.h"


NetworkingState* Quiting::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	p_nwm->ResetTimeout(); //reincio el timeout.
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	p_nwm->Shutdown();
	return nullptr;
}

NetworkingState* Quiting::OnTimer(NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = nullptr;
	p_nwm->IncrementTime();
	if (p_nwm->TimeEnded())
	{
		char error_pckg[1] = { ERROR_HEADER };
		p_state = new Quiting;
		Gm->SetExit(true);
		Gm->setMessage("Se perdio la comunicacion, cerrando...");
		p_nwm->sendPackage(error_pckg, 1);
		p_nwm->Shutdown();
	}
	return p_state;
}