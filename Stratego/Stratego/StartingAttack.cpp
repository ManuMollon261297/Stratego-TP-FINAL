#include "StartingAttack.h"
#include "NetworkingFuncs.h"
#include "currStatus.h"

NetworkingState* StartingAttack::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	unsigned char enemy_rank = (ev.GetRecieved())[1]; 
	NetworkingState* p_state;
	if (!(ValidateRank(enemy_rank)) ) //si el rank es invalido es un error de comunicacion.
	{
		char pckg[1];
		pckg[0] = ERROR_HEADER;
		p_nwm->sendPackage(pckg, 1);
		p_state = new Quiting;
	}
	else
	{
		rank enemy = GetRank(enemy_rank);
		Gm->resolveAttack(enemy);
		if (((Gm->getState()) == GAME_OVER) || (!(Gm->verifyMovement()))) //Se capturo el flag, o no hay pieza mobiles, gana el enemigo.
		{
			char pckg[1];
			pckg[0]= (YOU_WON_HEADER);
			Gm->setState(GAME_OVER);
			p_nwm->sendPackage(pckg, 1);
			p_state = new WaitingPlayerDecision;
		}
		else //si no gano el otro, mando un paquete de attack con mi rank para que pueda resolver el ataque.
		{
			char pckg[2];
			pckg[0] = ATTACK_HEADER;
			currStatus enemy_status = Gm->GetopPosStatus();
			rank my_rank = (Gm->getRankFromPos(enemy_status.next));
			unsigned char rank2send = ConvertRankToPackageFormat(my_rank);
			pckg[1] = rank2send;
			Gm->setState(OP_TURN);
			p_nwm->sendPackage(pckg, 2);
			p_state = new WaitingMove;
		}
	}

	return p_state;


}