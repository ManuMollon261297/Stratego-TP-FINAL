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

		p_nwm->setServer(CLIENT);
		p_nwm->SetServerFinishedPlacing(false);
		Gm->updateLeaderboard(p_nwm->getMe()); //Actualizo que gane.
		Gm->reset();//Prepara todo para una partida nueva.
		Gm->setState(PLACING_FICHAS);
		Gm->setMessage("Place your tokens");
		sent = p_nwm->sendPackage(pckg, 1);
		if (!sent)
		{
			Gm->SetExit(true);
			p_state = new Quiting;
		}
	}
	else if (Gm->getState() == GAME_OVER_SELECTED)
	{
		bool sent = false;
		std::string aux;
		NetworkingState* p_state = new Quiting;

		char pckg[1] = { GAME_OVER_HEADER };
		p_nwm->ResetTimeout();
		DoLeaderBoardRoutine(Gm, p_nwm->getMe()); //Actualzo que gane.
		sent = p_nwm->sendPackage(pckg, 1);
		if (!sent) //error de comunicacion.
		{
			p_nwm->Shutdown();
			Gm->setMessage("Communication error, closing...");
			Gm->SetExit(true);
		}
		
		return p_state;
	}
	else
	{
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
		Gm->updateLeaderboard(p_nwm->getMe()); //Actializa que gane.
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;

	}
	return p_state;
}