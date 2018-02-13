#include "WaitingNewGameResponse.h"

WaitingNewGameResponse::WaitingNewGameResponse()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingNewGameResponse" << std::endl;

#endif //DEBUG
}


NetworkingState* WaitingNewGameResponse::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state= nullptr;
	p_nwm->SetServerFinishedPlacing(true);

	if (Gm->getState() == ENDING_PLACING_FICHAS) //Si ya termine de posicionar las fichas
	{
		p_nwm->SetServerFinishedPlacing(false); //Reseteo el flag

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
		p_state = new NetPlacingFichas;
	}
	return p_state;
}

NetworkingState* WaitingNewGameResponse::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char pckg[1] = { ACK_HEADER };
	NetworkingState* p_state = new Quiting;
	Gm->setMessage("Oponent exit, quiting...");
	Gm->SetExit(true);
	p_nwm->sendPackage(pckg, 1);
	p_nwm->Shutdown();
	return p_state;
}

NetworkingState* WaitingNewGameResponse::EndedPlacing(NetworkingModel* p_nwm, GameModel * Gm)
{
	return nullptr;
}