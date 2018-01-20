#include "Quiting.h"


NetworkingState* Quiting::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	return nullptr;
}