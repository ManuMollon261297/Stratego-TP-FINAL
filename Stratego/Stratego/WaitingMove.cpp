#include "WaitingMove.h"
#include "pos.h"
#include "ranks.h"
#include "NetworkingFuncs.h"


WaitingMove::WaitingMove()
{
#ifdef DEBUG

	std::cout << std::endl << "In WaitingMove" << std::endl;

#endif //DEBUG
}



NetworkingState* WaitingMove::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState * p_state = nullptr;
	Gm->setState(OP_TURN); //Es el turno del oponente.
	p_nwm->ResetTimeout(); //Se reinicia el timeout limite.
	std::string pckg = ev.GetRecieved();
	int original_posY = pckg[1] - 'A'; //Le resta el valor de la primera columna para obtener el numero.
	int original_posX = pckg[2] - 1; //le resta uno porque tomamos posiciones de 0 a 9 y llegan de 1 a 10.

	int destination_posY = pckg[3] - 'A';
	int destination_posX = pckg[4] - 1;

	pos origin(original_posX, original_posY);
	pos destination(destination_posX, destination_posY);
	if (!(Gm->getRed())) //Si soy azul invierto las posiciones
	{
		InvertPositionToLayout(&origin);
		InvertPositionToLayout(&destination);
	}
	if ( !(ValidateMovement(Gm, origin, destination)) )
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	else
	{
		if (!(Gm->move(origin, destination))) //Si devuelve false es porque el move fue un ataque.
		{
			notstd::rank my_rank = Gm->getRankFromPos(destination);
			unsigned char rank2send = ConvertRankToPackageFormat(my_rank); //rank en el formato valido para el paquete.
			pckg.clear();
			pckg.push_back(ATTACK_HEADER);
			pckg.push_back(rank2send);
			sent = p_nwm->sendPackage((char*)pckg.c_str(), 2); //Mando el paquete de attack.
			if (sent)
			{
				p_state = new WaitingAttack;
			}
			else
			{
				ErrorRoutine(p_nwm, Gm);
				p_state = new Quiting;
			}

		}
		else //El move no fue un ataque
		{
			Gm->setState(MY_TURN); //Ya se realizo la movida del oponente asique es mi turno.
			Gm->setMessage("Please Make a move");
			Gm->restartTimer();
			p_state = nullptr; //No cambia de estado.
		}
	}

	return p_state;
}

NetworkingState* WaitingMove::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER); 
	Gm->playerWon();
	p_nwm->ResetTimeout(); //Se reinicia el timeout limite.
	Gm->setMessage("Enemy's time up or couldn't move");
	NetworkingState * p_state = new WaitingPlayerDecision;
	return p_state;


}

NetworkingState* WaitingMove::MoveDone(NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState* p_state = nullptr;
	bool sent = false;
	if (Gm->getMoveDone()) //El usuario hizo un movimiento valido
	{
		Gm->setMoveDoneFalse();
		Gm->restartTimer();
		pos origin = Gm->GetmyPosStatus().previous;
		pos des = Gm->GetmyPosStatus().next;
		if (!(Gm->getRed())) //Si soy azul invierto las posiciones
		{
			InvertPositionToLayout(&origin);
			InvertPositionToLayout(&des);
		}
		char move_pckg[5];
		move_pckg[0] = MOVE_HEADER;
		char or_col = 'A' + (char)(origin.y);
		char or_row = 1 + (origin.x);
		char des_col = 'A' + (char)(des.y);
		char des_row = 1 + (des.x);
		move_pckg[1] = or_col;
		move_pckg[2] = or_row;
		move_pckg[3] = des_col;
		move_pckg[4] = des_row;
		sent = p_nwm->sendPackage(move_pckg, 5); //Manda el paquete de move.

		Gm->setState(OP_TURN);
		Gm->setMessage("Opponents turn");
	}
	if (!sent) //Error de comunicacion.
	{
		ErrorRoutine(p_nwm, Gm);
		p_state = new Quiting;
	}
	return p_state; //Si es pasivo espero un move

}

NetworkingState* WaitingMove::AttackDone(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;
	if (Gm->getMoveDone()) //El usuario hizo un movimiento valido
	{
		Gm->setMoveDoneFalse();
		Gm->restartTimer();
		pos origin = Gm->GetmyPosStatus().previous;
		pos des = Gm->GetmyPosStatus().next;
		if (!(Gm->getRed())) //Si soy azul invierto las posiciones
		{
			InvertPositionToLayout(&origin);
			InvertPositionToLayout(&des);
		}
		char move_pckg[5];
		move_pckg[0] = MOVE_HEADER;
		char or_col = 'A' + (char)(origin.y);
		char or_row = 1 + (origin.x);
		char des_col = 'A' + (char)(des.y);
		char des_row = 1 + (des.x);
		move_pckg[1] = or_col;
		move_pckg[2] = or_row;
		move_pckg[3] = des_col;
		move_pckg[4] = des_row;
		sent = p_nwm->sendPackage(move_pckg, 5); //Manda el paquete de move.

		if (sent)
		{
			p_state = new StartingAttack; //Si es ofensivo espero un ataque.
		}
		else
		{
			ErrorRoutine(p_nwm, Gm);
			p_state = new Quiting;
		}
		
	}
	return p_state;
}

NetworkingState* WaitingMove::OnTimer(NetworkingModel* p_nwm, GameModel * Gm, MenuModel* MM)
{
	NetworkingState* p_state = nullptr;
	bool sent = false;
	if ((Gm->getState()) == MY_TURN)
	{
		Gm->decrementTime();
		if ((Gm->getTime()) == 0) //Gana el otro jugador por tardar demaasiado.
		{
			char pckg[1] = { YOU_WON_HEADER };
			Gm->setState(GAME_OVER);
			Gm->setMessage("Defeat! Time's up");
			sent = p_nwm->sendPackage(pckg, 1);
			if (sent)
			{
				p_state = new WaitingOponentDecision; 
			}
			else
			{
				ErrorRoutine(p_nwm, Gm);
				p_state = new Quiting;
			}
		}
		else if ((Gm->getTime()) == 60)
		{
			Gm->setMessage("Less than a minute left");
		}
		else if ((Gm->getTime()) == 10)
		{
			Gm->setMessage("Running out of time!");
		}
	}
	else if ((Gm->getState()) == OP_TURN) //Si pasan 2 minutos y medio
	{									//se asume que se perdio la comunicacion.
		p_nwm->IncrementTime();
		if (p_nwm->TimeEnded())
		{
			ErrorRoutine(p_nwm, Gm);
			p_state = new Quiting;
		}
	}
	return p_state;
	
}

