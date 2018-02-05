#include "WaitingWhoStart.h"


NetworkingState* WaitingWhoStart::I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1];
	NetworkingState* p_state;
	bool sent = false;
	Gm->setRed(false);
	pckg[0] = ACK_HEADER;
	sent = p_nwm->sendPackage(pckg, 1);
	if (sent)
	{
		p_state = new NetPlacingFichas;
		Gm->setState(PLACING_FICHAS);
	}
	else //se perdio la comunicacion.
	{
		Gm->SetExit(true);
		p_state = new Quiting;
	}
	return p_state;
}

NetworkingState* WaitingWhoStart::You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1];
	NetworkingState* p_state;
	bool  sent = false;
	Gm->setRed(true);
	pckg[0] = ACK_HEADER;
	sent = p_nwm->sendPackage(pckg, 1);
	if (sent)
	{
		p_state = new NetPlacingFichas;
		Gm->setState(PLACING_FICHAS);
	}
	else
	{
		Gm->SetExit(true);
		p_state = new Quiting;
	}
	
	return p_state;
}
