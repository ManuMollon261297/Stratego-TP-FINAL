#include "Quiting.h"


Quiting::Quiting()
{
#ifdef DEBUG

	std::cout << std::endl << "In Quiting" << std::endl;

#endif //DEBUG
}


NetworkingState* Quiting::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm, MenuModel* p_mm)
{
	p_nwm->ResetTimeout(); //reincio el timeout.
	Gm->SetExit(true);
	p_nwm->Shutdown();
	return nullptr;
}

NetworkingState* Quiting::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
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