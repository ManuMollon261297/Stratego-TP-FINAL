#include "WaitingAttack.h"

WaitingAttack::WaitingAttack()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingAttack" << std::endl;

#endif //DEBUG
}

NetworkingState* WaitingAttack::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;
	std::string pckg = ev.GetRecieved();
	unsigned char enemy_rank = pckg[1];
	p_nwm->ResetTimeout(); //Se reinicia el timeout limite.
	if ( !ValidateRank(enemy_rank)) 
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	else 
	{
		notstd::rank rank_recieved = GetRank(enemy_rank);
		Gm->resolveAttack(rank_recieved);
		Gm->setAttackResolvedFalse();
		if (Gm->getState() == GAME_OVER)
		{
			if (Gm->didPlayerWin())
			{
				Gm->setMessage("Enemy flag was taken");
				p_state = new WaitingYouWon;
			}
			else
			{
				pckg.clear();
				pckg.push_back(YOU_WON_HEADER);
				sent = p_nwm->sendPackage((char*)pckg.c_str(), 1);
				if (sent)
				{
					Gm->setMessage("Your flag was taken");
					p_state = new WaitingOponentDecision;
				}
				else //Error de comunicacion.
				{
					ErrorRoutine(p_nwm, Gm);
					p_state = new Quiting;
				}
			}
		}
		else if (!(Gm->verifyMovement()))
		{
			Gm->setState(GAME_OVER);
			pckg.clear();
			pckg.push_back(YOU_WON_HEADER);
			sent = p_nwm->sendPackage((char*)pckg.c_str(), 1);
			if (sent)
			{
				Gm->setMessage("You had no valid movements");
				p_state = new WaitingOponentDecision;
			}
			else //Error de comunicacion.
			{
				ErrorRoutine(p_nwm, Gm);
				p_state = new Quiting;
			}
		}
		else
		{
			Gm->setState(MY_TURN);//Ya es mi turno, el otro debe esperar que responda con un move.
			Gm->restartTimer();
			Gm->setMessage("Please make a move");
			p_state = new WaitingMove;
		}
		
	}
	return p_state;
	
}

NetworkingState* WaitingAttack::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new WaitingPlayerDecision;
	Gm->setState(GAME_OVER);
	Gm->playerWon();
	p_nwm->ResetTimeout(); //Se reinicia el timeout limite.
	Gm->setMessage("Victory! you won");
	return p_state;
}

NetworkingState* WaitingAttack::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
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




