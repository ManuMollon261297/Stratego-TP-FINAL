#include "WaitingStartResponse.h"


NetworkingState* Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(PLACING_FICHAS);
	return new NetPlacingFichas;
}