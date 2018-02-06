#include "WaitingNameResponse.h"
#include <time.h>

NetworkingState* WaitingNameResponse::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state;
	bool sent = false;
	p_nwm->ResetTimeout();
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
			sent = p_nwm->sendPackage(pckg, 1);

		}
		else
		{
			Gm->setRed(true);
			pckg[0] = I_START_HEADER; //Si el numero sorteado es par, empieza el server.
			sent = p_nwm->sendPackage(pckg, 1);
		}
		p_state = new WaitingStartResponse;

	}
	else 
	{
		char pckg[1];
		pckg[0] = NAME_HEADER;
		sent = p_nwm->sendPackage(pckg, 1); //si soy el client pregunto el nombre del server y espero la respuesta.
		p_state = new WaitingNameIs;
	}

	if (!sent)
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	return p_state;
}

NetworkingState* WaitingNameResponse::OnTimer(NetworkingModel* p_nwm, GameModel * Gm)
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