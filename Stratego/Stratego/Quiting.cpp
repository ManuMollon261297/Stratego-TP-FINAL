#include "Quiting.h"


NetworkingState* Quiting::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state;
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	return p_state;
}