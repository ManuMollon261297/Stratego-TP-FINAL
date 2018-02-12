#include "WaitingPlayerDecision.h"

WaitingPlayerDecision::WaitingPlayerDecision()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingPlayerDecision" << std::endl;

#endif //DEBUG
}

NetworkingState* WaitingPlayerDecision::SelectedGameOver(NetworkingModel* NWM, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;
	char pckg[1] = { GAME_OVER_HEADER };
	p_state = new Quiting;
	Gm->setMessage("Sending choice...");
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
		Gm->setMessage("Sending choice...");
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
		Gm->setMessage("Place your tokens");
	}

	return p_state;
}