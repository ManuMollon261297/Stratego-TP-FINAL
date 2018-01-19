#include "WaitingNameIs.h"



NetworkingState* WaitingNameIs::Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* state;
	bool sent = false;
	char pckg[1];
	pckg[0] = ACK_HEADER;
	do
	{
		sent = p_nwm->sendPackage(pckg, 1);
	} while (!sent);

	if (p_nwm->getServer() == SERVER)
	{
		
		state=  new WaitingName; //si soy el server paso a waiting name
		
	}
	else
	{
		state = new WaitingWhoStart; //si soy el client paso a esperar el orden de jugada.
	}

	return state;
}
