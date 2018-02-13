#include "WaitingOponentDecision.h"

WaitingOponentDecision::WaitingOponentDecision()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingOponentDecision" << std::endl;

#endif //DEBUG
}


NetworkingState* WaitingOponentDecision::Play_again(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new WaitingPlayerDecision;
	Gm->setMessage("Opponent wants to play again");
	return p_state; 
}

NetworkingState* WaitingOponentDecision::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = new Quiting;
	char pckg[1] = { ACK_HEADER };
	Gm->SetExit(true);
	Gm->setMessage("Oponent exit, quiting...");
	sent = p_nwm->sendPackage(pckg, 1);
	p_nwm->Shutdown();
	return p_state;
}

NetworkingState* WaitingOponentDecision::SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = new Quiting;

	char pckg[1] = { QUIT_HEADER };
	p_nwm->ResetTimeout();
	sent = p_nwm->sendPackage(pckg, 1);
	if (!sent) //error de comunicacion.
	{
		p_nwm->Shutdown();
		Gm->setMessage("Communication error, closing...");
		Gm->SetExit(true);
	}
	else
	{
		Gm->setMessage("Ending communication...");
	}
	return p_state;
}
NetworkingState* WaitingOponentDecision::SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setMessage("Waiting for opponent's decision");
	return nullptr;
}