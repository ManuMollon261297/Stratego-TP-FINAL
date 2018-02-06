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
	NetworkingState* p_state;
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
		rank rank_recieved = GetRank(enemy_rank);
		Gm->resolveAttack(rank_recieved);
		if ( ((Gm->getState()) == GAME_OVER) || (!(Gm->verifyMovement())) ) //Se capturo el flag, o no hay pieza mobiles, gana el enemigo.
		{
			pckg.clear();
			pckg[0] = YOU_WON_HEADER;
			sent = p_nwm->sendPackage((char*)pckg.c_str(), 1);
			if (sent)
			{
				Gm->setMessage("Derrota! esperando decision del oponente");
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
			Gm->setMessage("Por favor realizar una jugada valida");
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
	Gm->setMessage("Victoria! has ganado");
	return p_state;
	//Habria que preguntarle al usuario de alguna forma si quiere volver a jugar de nuevo.
	//en base a eso mando GAME_OVER o PLAY_AGAIN.
}

NetworkingState* WaitingAttack::OnTimer(NetworkingModel* p_nwm, GameModel * Gm)
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




