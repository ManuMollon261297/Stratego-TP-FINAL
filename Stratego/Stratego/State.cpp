#include "State.h"
#include "NetworkingModel.h"

//Hay que agregar en todos los casos que mande un paquete de error antes del return nullptr,
//menos quit y error
//Hay que cerrrar la comunicacion despues de enviar el paquete de error.

NetworkingState:: ~NetworkingState()
{

}

NetworkingState* NetworkingState::Play_again(NetWorkingEvent& ev,  NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Name(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Name_is(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::I_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::You_start(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::R_u_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::I_am_ready(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}


NetworkingState* NetworkingState::Ack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Game_over(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}

NetworkingState* NetworkingState::Attack(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ERROR_HEADER };
	p_nwm->sendPackage(message, 1);
	return nullptr;
}


NetworkingState* NetworkingState::Quit(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	char message[1] = { ACK_HEADER };
	p_nwm->sendPackage(message, 1);
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	return nullptr;
}

NetworkingState* NetworkingState::Error(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	return nullptr;
}

NetworkingState* NetworkingState::EndedPlacing(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	do
	{
		sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.
	} while (!sent);

	return nullptr;
}
NetworkingState* NetworkingState::SelectedGameOver(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	do
	{
		sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.
	} while (!sent);

	return nullptr;
}
NetworkingState* NetworkingState::SelectedPlayAgain(NetworkingModel* p_nwm, GameModel * Gm)
{
	bool sent = false;
	char pckg[1] = { ERROR_HEADER };
	Gm->setState(GAME_OVER);
	Gm->SetExit(true);
	do
	{
		sent = p_nwm->sendPackage(pckg, 1); //Mando que hubo un error.
	} while (!sent);

	return nullptr;
}
NetworkingState* NetworkingState::MoveDone(NetworkingModel* NWM, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;
	if (Gm->getMoveDone()) //El usuario hizo un movimiento valido
	{
		Gm->setMoveDoneFalse();
		char move_pckg[5];
		move_pckg[0] = MOVE_HEADER;
		char or_col = 'A' + (char)((Gm->GetmyPosStatus()).previous.y);
		char or_row = 1 + ((Gm->GetmyPosStatus()).previous.x);
		char des_col = 'A' + (char)((Gm->GetmyPosStatus()).next.y);
		char des_row = 1 + ((Gm->GetmyPosStatus()).next.x);
		move_pckg[1] = or_col;
		move_pckg[2] = or_row;
		move_pckg[3] = des_col;
		move_pckg[4] = des_row;
		do
		{
			sent = NWM->sendPackage(move_pckg, 5); //Manda el paquete de move.
		} while (!sent);

		p_state = new WaitingMove; //Si es pasivo espero un move
		Gm->setState(OP_TURN);
	}
	return p_state;
}
NetworkingState* NetworkingState::AttackDone(NetworkingModel* NWM, GameModel * Gm)
{
	bool sent = false;
	NetworkingState* p_state = nullptr;
	if (Gm->getMoveDone()) //El usuario hizo un movimiento valido
	{
		Gm->setMoveDoneFalse();
		char move_pckg[5];
		move_pckg[0] = MOVE_HEADER;
		char or_col = 'A' + (char)((Gm->GetmyPosStatus()).previous.y);
		char or_row = 1 + ((Gm->GetmyPosStatus()).previous.x);
		char des_col = 'A' + (char)((Gm->GetmyPosStatus()).next.y);
		char des_row = 1 + ((Gm->GetmyPosStatus()).next.x);
		move_pckg[1] = or_col;
		move_pckg[2] = or_row;
		move_pckg[3] = des_col;
		move_pckg[4] = des_row;
		do
		{
			sent = NWM->sendPackage(move_pckg, 5); //Manda el paquete de move.
		} while (!sent);

		p_state = new StartingAttack; //Si es ofensivo espero un ataque.
		Gm->setState(OP_TURN);
	}
	return p_state;
}
