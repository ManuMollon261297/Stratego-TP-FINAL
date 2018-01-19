#include "NetPlacingFichas.h"

NetworkingState* NetPlacingFichas::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;

	if ( (p_nwm->getServer()) == CLIENT ) //Si me llega R_U_READY tengo que necesariamente ser el client
	{
		p_nwm->SetServerFinishedPlacing(true);
		if ( (Gm->getState())== ENDING_PLACING_FICHAS) //termine de posicionar mis fichas
		{
			p_nwm->SetServerFinishedPlacing(false);

			if (Gm->getRed()) //Si voy primero directamente mando mi primera jugada.
			{
				Gm->setState(MY_TURN);
				p_state = new WaitingMove;
			}
			else //si empieza el server respondo i am ready.
			{
				char pckg[1];
				pckg[0] = I_AM_READY_HEADER;
				do
				{
					sent = p_nwm->sendPackage(pckg, 1);
				}while(!sent);
				p_state = new WaitingMove;
			}
		}
		else
		{
			p_state = nullptr;
		}
	}
	else //error de comunicacion.
	{
		char error_pckg[1]; //Si el rank es invalido lo trata como un error en la comunicacion.
		error_pckg[0] = ERROR_HEADER;
		do
		{
			sent = p_nwm->sendPackage(error_pckg, 1);
		} while (!sent);
		p_state = new Quiting;
	}
	return p_state;
	
}

NetworkingState* NetPlacingFichas::I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState * p_state = nullptr;
	if (((p_nwm->getServer()) == SERVER) && (Gm->getRed())) //Si me llega i am ready tengo que ser server y ser el que empieza
	{
		Gm->setState(MY_TURN);

	}
	else //error de comunicacion.
	{
		char error_pckg[1]; //Si el rank es invalido lo trata como un error en la comunicacion.
		error_pckg[0] = ERROR_HEADER;
		do
		{
			sent = p_nwm->sendPackage(error_pckg, 1);
		} while (!sent);
		p_state = new Quiting;
	}
}