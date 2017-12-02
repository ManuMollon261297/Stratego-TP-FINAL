#include "WaitingNameResponse.h"
#include <time.h>

NetworkingState* WaitingNameResponse::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state;
	if (p_nwm->getServer() == SERVER)
	{
		//sorteo orden de jugada, envio los ordenes y espero la respuesta
		char pckg[1];
		unsigned int starting = 0;
		srand(time(NULL));
		if (rand() % 2)
		{
			Gm->setRed(false);
			pckg[0] = YOU_START_HEADER; //Si el numero sorteado es impar empieza el cliente.
			p_nwm->sendPackage(pckg, 1);
		}
		else
		{
			Gm->setRed(true);
			pckg[0] = I_START_HEADER; //Si el numero sorteado es par, empieza el server.
			p_nwm->sendPackage(pckg, 1);
		}
		p_state = new WaitingStartResponse;

	}
	else 
	{
		char pckg[1];
		pckg[0] = NAME_HEADER;
		p_nwm->sendPackage(pckg, 1); //si soy el client pregunto el nombre del server y espero la respuesta.
		p_state = new WaitingNameIs;
	}

	return p_state;
}