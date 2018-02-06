#include "WaitingNameIs.h"



NetworkingState* WaitingNameIs::Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* state;
	std::string recieved = ev.GetRecieved();
	unsigned int count = recieved[1];
	std::string opp_name;
	bool sent = false;
	char pckg[1];
	pckg[0] = ACK_HEADER;
	for (unsigned int i=0; i < count; ++i)
	{
		opp_name.push_back(recieved[2 + i]); //empiezo con offset porque este el header y el byte de count.
	}
	Gm->SetOpponentName(opp_name); //Guardo el nombre del oponente.
	sent = p_nwm->sendPackage(pckg, 1);

	if (sent)
	{
		if (p_nwm->getServer() == SERVER)
		{

			state = new WaitingName; //si soy el server paso a waiting name

		}
		else
		{
			state = new WaitingWhoStart; //si soy el client paso a esperar el orden de jugada.
		}
	}
	else //Se perdio la comunicacion.
	{
		ErrorRoutine(p_nwm, Gm);
		state = new Quiting;
	}

	return state;
}
