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
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
		
	}
	return p_state;
}