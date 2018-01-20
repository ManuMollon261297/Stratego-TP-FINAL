#include "WaitingAttack.h"



NetworkingState* WaitingAttack::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state;
	std::string pckg = ev.GetRecieved();
	unsigned char enemy_rank = pckg[1];
	if ( !ValidateRank(enemy_rank)) 
	{
		char error_pckg[1]; //Si el rank es invalido lo trata como un error en la comunicacion.
		error_pckg[0] = ERROR_HEADER;
		do
		{
			sent = p_nwm->sendPackage(error_pckg, 1);
		} while (!sent);
		Gm->setState(GAME_OVER);
		Gm->SetExit(true);
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
			do
			{
				sent = p_nwm->sendPackage((char*)pckg.c_str(), 1);
			} while (!sent);
			p_state = new WaitingPlayerDecision;
		}
		else
		{
			Gm->setState(MY_TURN);//Ya es mi turno, el otro debe esperar que responda con un move.
			p_state = new WaitingMove;
		}
		
	}
	
}

NetworkingState* WaitingAttack::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = new WaitingPlayerDecision;
	Gm->setState(GAME_OVER);
	Gm->playerWon();
	return p_state;
	//Habria que preguntarle al usuario de alguna forma si quiere volver a jugar de nuevo.
	//en base a eso mando GAME_OVER o PLAY_AGAIN.
}




