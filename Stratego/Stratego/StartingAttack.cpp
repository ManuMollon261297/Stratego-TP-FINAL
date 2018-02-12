#include "StartingAttack.h"
#include "NetworkingFuncs.h"
#include "currStatus.h"


StartingAttack::StartingAttack()
{
#ifdef DEBUG

	std::cout << std::endl << "In StartingAttack" << std::endl;

#endif //DEBUG
}


NetworkingState* StartingAttack::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	unsigned char enemy_rank = (ev.GetRecieved())[1]; 
	NetworkingState* p_state;
	p_nwm->ResetTimeout(); //Se reinicia el timeout limite.
	if (!(ValidateRank(enemy_rank)) ) //si el rank es invalido es un error de comunicacion.
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	else
	{
		notstd::rank enemy = GetRank(enemy_rank);
		Gm->resolveAttack(enemy);
		Gm->setAttackResolvedFalse();
		if ((Gm->getState()) == GAME_OVER)
		{
			if (!(Gm->didPlayerWin())) //Si gano el otro mando el header.
			{
				char pckg[1];
				pckg[0] = (YOU_WON_HEADER);
				sent = p_nwm->sendPackage(pckg, 1);
				p_state = new WaitingOponentDecision;
			}
			else
			{
				char pckg[2];
				pckg[0] = ATTACK_HEADER;
				notstd::rank my_rank = Gm->getMyRank();
				unsigned char rank2send = ConvertRankToPackageFormat(my_rank);
				pckg[1] = rank2send;
				sent = p_nwm->sendPackage(pckg, 2);
				p_state = new WaitingMove; //Tendria que ser Un estado que se llama WaitingYouWon.
			}
			
		}
		else if (!(Gm->verifyMovement())) //No quedan fichas moviles
		{
			char pckg[1];
			pckg[0] = (YOU_WON_HEADER);
			sent = p_nwm->sendPackage(pckg, 1);
			p_state = new WaitingOponentDecision;
		}
		
		else //si no gano el otro, mando un paquete de attack con mi rank para que pueda resolver el ataque.
		{
			char pckg[2];
			pckg[0] = ATTACK_HEADER;
			notstd::rank my_rank = Gm->getMyRank();
			unsigned char rank2send = ConvertRankToPackageFormat(my_rank);
			pckg[1] = rank2send;
			Gm->setState(OP_TURN);
			Gm->setMessage("Opponent's turn");
			sent = p_nwm->sendPackage(pckg, 2);
			p_state = new WaitingMove;
		}

		if (!sent) //Error de comunicacion.
		{
			ErrorRoutine(p_nwm, Gm);
			p_state = new Quiting;
		}
	}

	return p_state;


}

NetworkingState* StartingAttack::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
{
	NetworkingState* p_state = nullptr;
	p_nwm->IncrementTime();
	if ( p_nwm->TimeEnded() )
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
		
	}
	return p_state;
}