#include "WaitingWhoStart.h"


WaitingWhoStart::WaitingWhoStart(void)
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingWhoStart" << std::endl;

#endif //DEBUG
}

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
		Gm->setMessage("Posicione sus fichas");
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
		Gm->setMessage("Posicione sus fichas");
	}
	else
	{
		Gm->SetExit(true);
		p_state = new Quiting;
	}
	
	return p_state;
}
