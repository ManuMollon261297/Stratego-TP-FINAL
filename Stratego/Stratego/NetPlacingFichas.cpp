#include "NetPlacingFichas.h"


NetPlacingFichas::NetPlacingFichas()
{
#ifdef DEBUG

	std::cout << std::endl << "In NetPlacingFichas" << std::endl;

#endif //DEBUG
}


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
				Gm->restartTimer();
				Gm->setMessage("Please make a move");
				p_state = new WaitingMove;
			}
			else //si empieza el server respondo i am ready.
			{
				char pckg[1];
				pckg[0] = I_AM_READY_HEADER;
				sent = p_nwm->sendPackage(pckg, 1);
				if (sent)
				{
					Gm->setState(OP_TURN);
					Gm->setMessage("Opponent's turn");
					p_state = new WaitingMove;
				}
				else //Error de comunicacion.
				{
					ErrorRoutine(p_nwm, Gm);
					p_state = new Quiting;
				}
			}
		}
		else
		{
			p_state = nullptr;
		}
	}
	else //error de comunicacion.
	{
		ErrorRoutine(p_nwm, Gm);
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
		//Asumo que si me llega i am ready es porque ya mande r_u_ready.

		Gm->setState(MY_TURN); //Le indico al jugador que haga su jugada.
		Gm->restartTimer();
		p_state = new WaitingMove; 
	}
	else //error de comunicacion.
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	return p_state;
}


NetworkingState*  NetPlacingFichas::EndedPlacing(NetworkingModel* NWM, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;

	if (NWM->getServer() == SERVER)
	{
		if (Gm->getRed())//termine de poner las fichas y soy el que empieza
		{
			Gm->setState(WAITING_FOR_OPPONENTS_SELECTION);//Habria que revisar a que estado cambiar el game model aca. 
			Gm->setMessage("Waiting for opponent...");
			p_state = new NetPlacingFichas;
		}
		else
		{
			Gm->setState(OP_TURN); //El otro jugador comienza entonces espero su jugada.
			Gm->setMessage("Opponent's turn");
			p_state = new WaitingMove;
		}
		char pckg[1];
		pckg[0] = R_U_READY_HEADER;
		sent = NWM->sendPackage(pckg, 1);
		if (!sent)
		{
			ErrorRoutine(NWM, Gm);
			p_state = new Quiting;
		}
	}
	else if (NWM->getServer() == CLIENT)
	{
		if (NWM->GetServerFinishedPlacing())
		{
			NWM->SetServerFinishedPlacing(false);
			p_state = new WaitingMove;

			if (Gm->getRed()) //Si voy primero directamente mando mi primera jugada.
			{
				Gm->setState(MY_TURN);
				Gm->setMessage("Please make a move");
			}
			else //si empieza el server respondo i am ready.
			{
				Gm->setState(OP_TURN);
				Gm->setMessage("Opponent's turn");
				char pckg[1];
				pckg[0] = I_AM_READY_HEADER;
				sent = NWM->sendPackage(pckg, 1);
				if (!sent)
				{
					ErrorRoutine(NWM, Gm);
					p_state = new Quiting;
				}

			}
		}
	}
	else //error de comunicacion.
	{
		ErrorRoutine(NWM, Gm);
		p_state = new Quiting;
	}
	return p_state;
}