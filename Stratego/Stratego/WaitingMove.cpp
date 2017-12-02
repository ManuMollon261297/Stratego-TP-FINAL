#include "WaitingMove.h"
#include "pos.h"
#include "ranks.h"
#include "NetworkingFuncs.h"






NetworkingState* WaitingMove::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	NetworkingState * p_state;
	Gm->setState(OP_TURN); //Empieza el turno del oponente.
	std::string pckg = ev.GetRecieved();
	int original_posY = pckg[1] - 'A'; //Le resta el valor de la primera columna para obtener el numero.
	int original_posX = pckg[2] - 1; //le resta uno porque tomamos posiciones de 0 a 9 y llegan de 1 a 10.

	int destination_posY = pckg[3] - 'A';
	int destination_posX = pckg[4] - 1;

	pos origin(original_posX, original_posY);
	pos destination(destination_posX, destination_posY);
	if ( !(ValidateMovement(Gm, origin, destination)) )
	{
		char error_pckg[1]; //Si el movimiento es invalido significa que hubo un error en la comunicacion.
		error_pckg[0] = ERROR_HEADER;
		p_nwm->sendPackage(error_pckg, 1);
		p_state = new Quiting;
	}
	else
	{
		if (!(Gm->move(origin, destination))) //Si devuelve false es porque el move fue un ataque.
		{
			rank my_rank = Gm->getRankFromPos(destination);
			unsigned char rank2send = ConvertRankToPackageFormat(my_rank); //rank en el formato valido para el paquete.
			pckg.clear();
			pckg[0] = ATTACK_HEADER;
			pckg[1] = rank2send;
			p_nwm->sendPackage((char*)pckg.c_str(), 2); //Mando el paquete de attack.
			p_state = new WaitingAttack;

		}
		else //El move no fue un ataque
		{
			p_state = nullptr; //No cambia de estado.
		}
	}

	return p_state;
}

NetworkingState* WaitingMove::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER);
	//Habria que preguntarle al usuario de alguna forma si quiere volver a jugar de nuevo.
	//en base a eso mando GAME_OVER o PLAY_AGAIN.
}

