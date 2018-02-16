#include "WaitingPlayerDecision.h"

WaitingPlayerDecision::WaitingPlayerDecision()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingPlayerDecision" << std::endl;

#endif //DEBUG
}

NetworkingState* WaitingPlayerDecision::SelectedGameOver(NetworkingModel* NWM, GameModel * Gm)
{
	std::string aux;
	bool sent = false;
	NetworkingState* p_state = nullptr;
	char pckg[1] = { GAME_OVER_HEADER };
	p_state = new Quiting;

	if (Gm->didPlayerWin())
	{
		if (Gm->updateLeaderboard(NWM->getMe())) //Actualizo que gane.
		{
			aux += "The win count of " + (NWM->getMe());
			aux += " was increased";
			Gm->setMessage((char*)aux.c_str());
		}
		else //Si no encontro el nombre lo escribi y crea un nuevo contador de victorias.
		{
			aux += "Created a win count for " + (NWM->getMe());
			Gm->setMessage((char*)aux.c_str());
		}
	}
	else
	{
		if (Gm->updateLeaderboard(Gm->GetOpponentName())) //Actualizo que gano el otro jugador.
		{
			aux += "The win count of " + (Gm->GetOpponentName());
			aux += " was increased";
			Gm->setMessage((char*)aux.c_str());
		}
		else //Si no encontro el nombre lo escribe y crea un nuevo contador de victorias.
		{
			aux += "Created a win count for " + (Gm->GetOpponentName());
			Gm->setMessage((char*)aux.c_str());
		}
	}
	NWM->ResetTimeout();
	sent = NWM->sendPackage(pckg, 1);
	if (!sent)
	{
		Gm->SetExit(true);
	}
	return p_state;
}

NetworkingState* WaitingPlayerDecision::SelectedPlayAgain(NetworkingModel* NWM, GameModel * Gm)
{
	bool sent = false;
	char pckg[1];
	NetworkingState* p_state = nullptr;
	if (Gm->didPlayerWin()) //Caso en el que quiero jugar de nuevo y gane
	{
		pckg[0] = (PLAY_AGAIN_HEADER);
		p_state = new WaitingNewGameResponse;

		NWM->setServer(CLIENT);
		NWM->SetServerFinishedPlacing(false);
		Gm->updateLeaderboard(NWM->getMe()); //Actualizo que gane.
		Gm->reset();//Prepara todo para una partida nueva.
		Gm->setState(PLACING_FICHAS);
		Gm->setMessage("Place your tokens");
		sent = NWM->sendPackage(pckg, 1);
		if (!sent)
		{
			Gm->setMessage("Comm error, quitting...");
			Gm->SetExit(true);
			p_state = new Quiting;
		}

	}
	else //Caso en el que quiero jugar de nuevo y perdi.
	{
		p_state = new NetPlacingFichas;
		Gm->updateLeaderboard(Gm->GetOpponentName()); //Actualizo que gano el otro.
		Gm->reset(); //Reestablece el tablero para volver a jugar.
		Gm->setState(PLACING_FICHAS);
		NWM->setServer(SERVER);
		Gm->setMessage("Place your tokens");
	}

	return p_state;
}