#include "WaitingWhoStart.h"


GenericState* WaitingWhoStart::I_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1];
	GenericState* p_state;
	Gm->setRed(false);
	pckg[0] = ACK_HEADER;
	p_nwm->sendPackage(pckg, 1);
	p_state = new PlacingFichas;
	Gm->setState(PLACING_FICHAS);
	return p_state;
}

GenericState* WaitingWhoStart::You_start(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1];
	GenericState* p_state;
	Gm->setRed(true);
	pckg[0] = ACK_HEADER;
	p_nwm->sendPackage(pckg, 1);
	p_state = new PlacingFichas;
	Gm->setState(PLACING_FICHAS);
	return p_state;
}
