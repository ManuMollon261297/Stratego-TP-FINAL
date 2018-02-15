#include "WaitingWhoStart.h"


WaitingWhoStart::WaitingWhoStart(void)
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingWhoStart" << std::endl;

#endif //DEBUG
}

NetworkingState* WaitingWhoStart::I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	char pckg[1];
	NetworkingState* p_state;
	bool sent = false;
	Gm->setRed(false);
	p_mm->setExit();
	p_mm = nullptr;
	pckg[0] = ACK_HEADER;
	sent = p_nwm->sendPackage(pckg, 1);
	if (sent)
	{
		p_state = new NetPlacingFichas;
		Gm->setState(PLACING_FICHAS);
		Gm->setMessage("Place your tokens");
	}
	else //se perdio la comunicacion.
	{
		Gm->SetExit(true);
		p_state = new Quiting;
	}
	return p_state;
}

NetworkingState* WaitingWhoStart::You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	char pckg[1];
	NetworkingState* p_state;
	bool  sent = false;
	Gm->setRed(true);
	p_mm->setExit();
	p_mm = nullptr;
	pckg[0] = ACK_HEADER;
	sent = p_nwm->sendPackage(pckg, 1);
	if (sent)
	{
		p_state = new NetPlacingFichas;
		Gm->setState(PLACING_FICHAS);
		Gm->setMessage("Place your tokens");
	}
	else
	{
		Gm->SetExit(true);
		p_state = new Quiting;
	}
	
	return p_state;
}
