#include "WaitingPlayerDecision.h"

NetworkingState* WaitingPlayerDecision::SelectedGameOver(NetworkingModel* NWM, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;
	char pckg[1] = { GAME_OVER_HEADER };
	p_state = new Quiting;
	Gm->setState(WAITING_FOR_OPPONENTS_SELECTION); //Chequear si es el estado que corresponde
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
	//Hay que ver Como Reiniciar todo el GameModel para prepararlo para
	//un juego nuevo.
	if (Gm->didPlayerWin()) //Caso en el que quiero jugar de nuevo y gane
	{
		pckg[0] = (PLAY_AGAIN_HEADER);
		p_state = new WaitingNewGameResponse;
		Gm->setState(WAITING_FOR_OPPONENTS_SELECTION); //Chequear si es el estado que corresponde
		sent = NWM->sendPackage(pckg, 1);
		if (!sent)
		{
			Gm->SetExit(true);
			p_state = new Quiting;
		}

	}
	else //Caso en el que quiero jugar de nuevo y perdi.
	{
		p_state = new NetPlacingFichas;
		Gm->setState(PLACING_FICHAS);
		NWM->setServer(SERVER);
		Gm->setRed(!(Gm->getRed())); //Se alterna el turno de quien empieza la partida.
	}

	return p_state;
}