#include "WaitingStartResponse.h"


NetworkingState* WaitingStartResponse::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	p_nwm->ResetTimeout();
	Gm->setState(PLACING_FICHAS);
	return new NetPlacingFichas;
}

NetworkingState* WaitingStartResponse::OnTimer(NetworkingModel* p_nwm, GameModel * Gm)
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
