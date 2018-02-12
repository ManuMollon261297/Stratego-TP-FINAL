#include "WaitingYouWon.h"

WaitingYouWon::WaitingYouWon()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingYouWon" << std::endl;

#endif //DEBUG
}

NetworkingState* WaitingYouWon::You_won(NetWorkingEvent&, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState * p_state = nullptr;
	if (Gm->getState() == PLAY_AGAIN_SELECTED)
	{
		char pckg[1];
		pckg[0] = (PLAY_AGAIN_HEADER);
		p_state = new WaitingNewGameResponse;
		Gm->setState(WAITING_FOR_OPPONENTS_SELECTION); //Chequear si es el estado que corresponde
		Gm->setMessage("Sending choice...");
		sent = p_nwm->sendPackage(pckg, 1);
		if (!sent)
		{
			Gm->SetExit(true);
			p_state = new Quiting;
		}
	}
	else if (Gm->getState() == GAME_OVER_SELECTED)
	{
		NetworkingState* p_state = nullptr;
		char pckg[1] = { GAME_OVER_HEADER };
		p_state = new Quiting;
		Gm->setState(WAITING_FOR_OPPONENTS_SELECTION); //Chequear si es el estado que corresponde
		Gm->setMessage("Sending choice...");
		sent = p_nwm->sendPackage(pckg, 1);
		if (!sent)
		{
			Gm->SetExit(true);
		}
		return p_state;
	}
	else
	{
		Gm->setMessage("Victory! you won");
		p_state = new WaitingPlayerDecision;
	}
	
	return p_state;
}

NetworkingState*  WaitingYouWon::SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm)
{
	return nullptr;
}

NetworkingState*  WaitingYouWon::SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm)
{
	return nullptr;
}

NetworkingState* WaitingYouWon::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
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