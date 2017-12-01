#include "WaitingStartResponse.h"


GenericState* Ack(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(PLACING_FICHAS);
	return new PlacingFichas;
}