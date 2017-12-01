#include "WaitingMove.h"
#include "pos.h"
#include "ranks.h"


bool ValidateMovement(GameModel * Gm, pos ori, pos des);
//Funcion que valida que el movimiento del oponente sea valido.
//Devuelve false si es invalida, y true si es valida.




GenericState* WaitingMove::Move(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	GenericState * p_state;
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
			unsigned char rank2send; //rank en el formato valido para el paquete.
			if ( (my_rank>=0)&&(my_rank<=8) )
			{
				rank2send = '1' + (unsigned char)my_rank;
			}
			else if (my_rank == FLAG)
			{
				rank2send = 'F';
			}
			else if (my_rank == BOMB)
			{
				rank2send = 'B';
			}
			else if (my_rank == SPY)
			{
				rank2send = 'S';
			}
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

GenericState* WaitingMove::You_won(NetWorkingEvent& ev, NetworkingModel* p_nwm, GameModel * Gm)
{
	Gm->setState(GAME_OVER);
	//Habria que preguntarle al usuario de alguna forma si quiere volver a jugar de nuevo.
	//en base a eso mando GAME_OVER o PLAY_AGAIN.
}


bool ValidateMovement(GameModel * Gm, pos ori, pos des)
{
	if( ((ori.x)< 0) || ((ori.x)>9) || ((ori.y)< 0) || ((ori.y)>9)) //Si alguna posicion se va de rango es invalida
	{
		return false;
	}
	else if (((des.x)< 0) || ((des.x)>9) || ((des.y)< 0) || ((des.y)>9))
	{
		return false;
	}
	else if (ori == des) //no puede llegar que se mueve a la misma posicion.
	{
		return false;
	}
		
	rank rank_in_origin = Gm->getRankFromPos(ori);
	rank rank_in_destination = Gm->getRankFromPos(des);
	bool valid = true;

	if ( (rank_in_origin != OTHERS) )
	{
		valid = false; //Es invalido si la fichaa que desea mover no es suya
	}
	else if ( (rank_in_destination == WATER) || (rank_in_destination == OTHERS) )
	{
		valid = false; //es invalido si desea moverla al agua o sobre otra de sus fichas
	}
	else if ( ((ori.x) != (des.x)) && ((ori.y) != (des.y)))
	{
		valid = false; //es invalido si el destino no esta sobre la misma fila o columna que el origen.
	}
	else if ( (ori.x) == (des.x) )
	{
		int offset = 0; //Espacio entre las posiciones elegidas.
		if ((ori.y) > (des.y))
		{
			offset = (ori.y) - (des.y) -1;
			pos recorrido;
			recorrido.x = ori.x;
			//Se fija que todos los espacios entre las dos posiciones esten vacios.
			for (int i = 1; (i <= offset) && (valid); i++)
			{
				recorrido.y = (ori.y) - i;
				if ( (Gm->getRankFromPos(recorrido)) != LAND )
				{
					valid = false;
				}
			}

		}
		else
		{
			offset = (des.y) - (ori.y) - 1;
			pos recorrido;
			recorrido.x = ori.x;
			//Se fija que todos los espacios entre las dos posiciones esten vacios.
			for (int i = 1; (i <= offset) && (valid); i++)
			{
				recorrido.y = (ori.y) + i;
				if ((Gm->getRankFromPos(recorrido)) != LAND)
				{
					valid = false;
				}
			}
		}
	}
	else if( (ori.y) == (des.y) )
	{
		int offset = 0; //Espacio entre las posiciones elegidas.
		if ((ori.x) > (des.x))
		{
			offset = (ori.x) - (des.x) - 1;
			pos recorrido;
			recorrido.y = ori.y;
			//Se fija que todos los espacios entre las dos posiciones esten vacios.
			for (int i = 1; (i <= offset) && (valid); i++)
			{
				recorrido.x = (ori.x) - i;
				if ((Gm->getRankFromPos(recorrido)) != LAND)
				{
					valid = false;
				}
			}

		}
		else
		{
			offset = (des.y) - (ori.y) - 1;
			pos recorrido;
			recorrido.y = ori.y;
			//Se fija que todos los espacios entre las dos posiciones esten vacios.
			for (int i = 1; (i <= offset) && (valid); i++)
			{
				recorrido.x = (ori.x) + i;
				if ((Gm->getRankFromPos(recorrido)) != LAND)
				{
					valid = false;
				}
			}
		}

	}

	return valid;
}