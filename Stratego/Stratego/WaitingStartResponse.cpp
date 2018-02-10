#include "WaitingStartResponse.h"

WaitingStartResponse::WaitingStartResponse(void)
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingStartResponse" << std::endl;

#endif //DEBUG
}

NetworkingState* WaitingStartResponse::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	p_nwm->ResetTimeout();
	Gm->setState(PLACING_FICHAS);
	return new NetPlacingFichas;
	Gm->setMessage("Place your tokens");
}

NetworkingState* WaitingStartResponse::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
{
	NetworkingState* p_state = nullptr;
	p_nwm->IncrementTime();
	if (p_nwm->TimeEnded())
	{
		
		p_state = new Quiting;
		ErrorRoutine(p_nwm, Gm);
	}
	return p_state;
}
