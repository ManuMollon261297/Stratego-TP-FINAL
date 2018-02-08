#include "NetworkingFuncs.h"

bool ValidateMovement(GameModel * Gm, pos ori, pos des)
{
	if (((ori.x)< 0) || ((ori.x)>9) || ((ori.y)< 0) || ((ori.y)>9)) //Si alguna posicion se va de rango es invalida
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

	notstd::rank rank_in_origin = Gm->getRankFromPos(ori);
	notstd::rank rank_in_destination = Gm->getRankFromPos(des);
	bool valid = true;

	if ((rank_in_origin != OTHERS))
	{
		valid = false; //Es invalido si la fichaa que desea mover no es suya
	}
	else if ((rank_in_destination == WATER) || (rank_in_destination == OTHERS))
	{
		valid = false; //es invalido si desea moverla al agua o sobre otra de sus fichas
	}
	else if (((ori.x) != (des.x)) && ((ori.y) != (des.y)))
	{
		valid = false; //es invalido si el destino no esta sobre la misma fila o columna que el origen.
	}
	else if ((ori.x) == (des.x))
	{
		int offset = 0; //Espacio entre las posiciones elegidas.
		if ((ori.y) > (des.y))
		{
			offset = (ori.y) - (des.y) - 1;
			pos recorrido;
			recorrido.x = ori.x;
			//Se fija que todos los espacios entre las dos posiciones esten vacios.
			for (int i = 1; (i <= offset) && (valid); i++)
			{
				recorrido.y = (ori.y) - i;
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
	else if ((ori.y) == (des.y))
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
			offset = (des.x) - (ori.x) - 1;
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

bool ValidateRank(unsigned char rank)
{
	bool valid = false;
	if ((rank >= '1') && (rank <= '9'))
	{
		valid = true;
	}
	else if ((rank == 'S') || (rank == 'B') || (rank == 'F'))
	{
		valid = true;
	}

	return valid;
}

notstd::rank GetRank(unsigned char pckg_rank)
{
	notstd::rank result= WATER;
	if ((pckg_rank >= '1') && (pckg_rank <= '9')) //Es una tropa comun
	{
		result = (notstd::rank)(pckg_rank - '1');
	}
	else
	{
		if (pckg_rank == 'S') //es un spy
		{
			result = SPY;
		}
		else if (pckg_rank == 'B') //es una  bomba
		{
			result = BOMB;
		}
		else if (pckg_rank == 'F') //es el flag
		{
			result = FLAG;
		}
	}
	return result;
}

unsigned char ConvertRankToPackageFormat(notstd::rank my_rank)
{
	unsigned char rank2send = '0'; //rank en el formato valido para el paquete.
	if ((my_rank >= 0) && (my_rank <= 8))
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
	return rank2send;
}