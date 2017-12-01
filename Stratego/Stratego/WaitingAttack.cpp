#include "WaitingAttack.h"


bool ValidateRank(unsigned char rank);
//Funcion que recibe el rank enviado por el oponente y valida que sea una de las opciones validas
//Devuelve false si e rank es invalido y true en caso contrario.

GenericState* WaitingAttack::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	GenericState* p_state;
	std::string pckg = ev.GetRecieved();
	unsigned char enemy_rank = pckg[1];
	if ( !ValidateRank(enemy_rank)) 
	{
		char error_pckg[1]; //Si el rank es invalidolo trata como un error en la comunicacion.
		error_pckg[0] = ERROR_HEADER;
		p_nwm->sendPackage(error_pckg, 1);
		p_state = new Quiting;
	}
	else 
	{
		Gm->resolveAttack(pckg[1]);
		if ( ((Gm->getState()) == GAME_OVER) || (!(Gm->verifyMovement())) ) //Se capturo el flag, o no hay pieza mobiles, gana el enemigo.
		{
			pckg.clear();
			pckg[0] = YOU_WON_HEADER;
			p_nwm->sendPackage((char*)pckg.c_str(), 1);
			p_state = new WaitingPlayerDecision;
		}
		else
		{
			//Ya es mi turno, el otro debe esperar que responda con un move.
			p_state = new WaitingMove;
		}
		
	}
	
}

GenericState* WaitingAttack::You_won(GenericEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER);
	//Habria que preguntarle al usuario de alguna forma si quiere volver a jugar de nuevo.
	//en base a eso mando GAME_OVER o PLAY_AGAIN.
}


bool ValidateRank(unsigned char rank)
{
	bool valid=false;
	if ((rank >= '1') && (rank <= '9'))
	{
		valid = true;
	}
	else if ( (rank == 'S')||(rank == 'B')||(rank == 'F') )
	{
		valid=true;
	}
	
	return valid;
}