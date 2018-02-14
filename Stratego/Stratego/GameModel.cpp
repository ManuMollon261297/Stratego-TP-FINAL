#include "GameModel.h"
#include "gameState.h"
//caso especial: 'r' ataca y 'q' defiende.
#define CASO_ESPECIAL(r, q) ( ((r == MINER) && (q == BOMB)) || ((r == SPY) && (q == MARSHAL)) )

GameModel::GameModel(): myPosStatus(0,0,0,0), opPosStatus(0, 0, 0, 0)
{
	//inicializacion del juego
	gameOver = false;

	Exit = false;

	moveDone = false;
	fichasPlaced = false;
	won = false;
	attackResolved = false;

	message = "Stratego";

	//inicializaciondel battlefield
	for (int i = 0;i<FILAS;i++)
	{
		for (int j=0;j<COLUMNAS;j++)
		{
			battlefield[i][j] = nullptr;
		}
	}
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<COLUMNAS; j++)
		{
			battlefield[i][j] = new ficha(OTHERS);
		}
	}
	for (int i = 4; i<6; i++)
	{
		for (int j = 2; j<4; j++)
		{
			battlefield[i][j] = new ficha(WATER);
		}
	}
	for (int i = 4; i<6; i++)
	{
		for (int j = 6; j<8; j++)
		{
			battlefield[i][j] = new ficha(WATER);
		}
	}
	//inicializacion de cemetery
	for (int i =0;i<TIPOS_DE_RANK;i++)
	{
		cemetery[i][0] = (MARSHAL + i); //rango que representa una fila
		cemetery[i][2] = 0;  // las fichas comienzan desseleccionadas. si se seleccionan, se setean con un '1'
	}
	cemetery[TIPOS_DE_RANK+1][0] = -1; //celda vacia sin info util
	//cantidad de fichas por cada rango
	cemetery[MARSHAL][1]= 1;
	cemetery[GENERAL][1]=1;
	cemetery[CORONEL][1]=2;
	cemetery[MAJOR][1]=3;
	cemetery[CAPTAIN][1]=4;
	cemetery[LIEUTENANT][1]=4;
	cemetery[SERGEANT][1]=4;
	cemetery[MINER][1]=5;
	cemetery[SCOUT][1]=8;
	cemetery[SPY][1]=1;
	cemetery[BOMB][1]=6;
	cemetery[FLAG][1]=1;
	cemetery[12][1]= 40; //total de fichas

	//inicializacion del state
	setState(PLACING_FICHAS);
	timeRemaining = 120; // El jugador tiene 120 segundos para decidir antes de perder.
	rescuesRemaining = 2;
	repeatMoveCounter = 0;
}

int GameModel::getState()
{
	return state;
}

void GameModel::setState(int state_)
{
	state = state_;
	std::cout << std::endl << state << std::endl; //Para debuggear
}

void GameModel::setAttackResolvedFalse(void)
{
	attackResolved = false;
}

bool GameModel::getRed()
{
	return red;
}

void GameModel::setRed(bool color)
{
	red = color;
}

std::string & GameModel::getMessage()
{
	return message;
}

void GameModel::setMessage(char * message_)
{
	message = message_;
	NotifyAllObservers();
}

bool GameModel::GetExit()const
{
	return Exit;
}

void GameModel::SetExit(bool value)
{
	Exit = value;
	NotifyAllObservers();
}

void GameModel::SetOpponentName(std::string str)
{
	opponents_name = str;
	NotifyAllObservers();
}

std::string& GameModel::GetOpponentName()
{
	return opponents_name;
}


bool GameModel::move(pos currPos, pos newPos)	// asume que en currpos hay una ficha movil valida
{												// devuelve true si se movio la ficha, false si es un ataque y todavia no se resolvio

	if (battlefield[newPos.x][newPos.y] == nullptr)
	{
		switch (state)
		{
			case MY_TURN: 
				setState(MY_MOVING); //esta linea verifica 
				myPosStatus.previous = currPos;								//que el movimiento no se haya repetido excesivamente
				myPosStatus.next = newPos;
				break;												
			case OP_TURN: 
				setState(OP_MOVING);
				opPosStatus.previous = currPos;
				opPosStatus.next = newPos;
				break;
		}
		if (state != MY_TURN) //validacion extra
		{
			battlefield[newPos.x][newPos.y] = battlefield[currPos.x][currPos.y];
			battlefield[currPos.x][currPos.y] = nullptr;
			moveDone = true;
		}
		NotifyAllObservers();
		return true;
	}
	else
	{
		switch (state)
		{
			case MY_TURN : 
				repeatMoveCounter = 0;
				setState(MY_ATTACKING);
				myPosStatus.previous = currPos;				
				myPosStatus.next = newPos;
				break;
			case OP_TURN: 
				setState(OP_ATTACKING);
				opPosStatus.previous = currPos;
				opPosStatus.next = newPos;
				break;
		}
		NotifyAllObservers();
		return false;
	}
}

void GameModel::resolveAttack(notstd::rank r)
{
	attackResolved = true;
	opRank = r;
	int aux = state;

	if (state == MY_ATTACKING)
	{
		myRank = battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank();
		if (r == FLAG)
		{
			aux = GAME_OVER;
			won = true;
			delete battlefield[myPosStatus.next.x][myPosStatus.next.y];
			battlefield[myPosStatus.next.x][myPosStatus.next.y] = battlefield[myPosStatus.previous.x][myPosStatus.previous.y];
			battlefield[myPosStatus.previous.x][myPosStatus.previous.y] = nullptr;
		}
		else if ((myRank != MINER)&&(r == BOMB))	//perdi, este caso no aparece en OP_ATTACKING porque las bombas
		{											//no pueden atacar
			if ((battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank() != notstd::rank::BOMB) && (battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank() != notstd::rank::FLAG))
			{
				cemetery[myRank][1]++;
				cemetery[13][1]++; //aumento fichas propias totales fuera del tablero
			}
			delete battlefield[myPosStatus.previous.x][myPosStatus.previous.y];
			battlefield[myPosStatus.previous.x][myPosStatus.previous.y] = nullptr;
		}
		else if (CASO_ESPECIAL(myRank, r) || (myRank < r))
		{
			delete battlefield[myPosStatus.next.x][myPosStatus.next.y];
			battlefield[myPosStatus.next.x][myPosStatus.next.y] = battlefield[myPosStatus.previous.x][myPosStatus.previous.y];
			battlefield[myPosStatus.previous.x][myPosStatus.previous.y] = nullptr; 
			aux = OP_TURN;
		}
		else if (myRank == r)
		{
			if ((battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank() != notstd::rank::BOMB) && (battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank() != notstd::rank::FLAG))
			{
				cemetery[myRank][1]++;
				cemetery[13][1]++; //aumento fichas propias totales fuera del tablero
			}
			delete battlefield[myPosStatus.previous.x][myPosStatus.previous.y];
			delete battlefield[myPosStatus.next.x][myPosStatus.next.y];
			battlefield[myPosStatus.previous.x][myPosStatus.previous.y] = nullptr;
			battlefield[myPosStatus.next.x][myPosStatus.next.y] = nullptr;
			aux = OP_TURN;
		}
		else //perdi
		{
			if ((battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank() != notstd::rank::BOMB) && (battlefield[myPosStatus.previous.x][myPosStatus.previous.y]->getRank() != notstd::rank::FLAG))
			{
				cemetery[myRank][1]++;
				cemetery[13][1]++; //aumento fichas propias totales fuera del tablero
			}
			delete battlefield[myPosStatus.previous.x][myPosStatus.previous.y];
			battlefield[myPosStatus.previous.x][myPosStatus.previous.y] = nullptr;
		}
	}
	else if (state == OP_ATTACKING)
	{
		myRank = battlefield[opPosStatus.next.x][opPosStatus.next.y]->getRank();
		if (myRank == FLAG)
		{
			aux = GAME_OVER;
			delete battlefield[opPosStatus.next.x][opPosStatus.next.y];
			battlefield[opPosStatus.next.x][opPosStatus.next.y] = battlefield[opPosStatus.previous.x][opPosStatus.previous.y];
			battlefield[opPosStatus.previous.x][opPosStatus.previous.y] = nullptr;
		}
		else if((CASO_ESPECIAL(r, myRank))||((r < myRank)&&(myRank != BOMB))) //entra si gano el opponent
		{
			if ((battlefield[opPosStatus.next.x][opPosStatus.next.y]->getRank() != notstd::rank::BOMB) && (battlefield[opPosStatus.next.x][opPosStatus.next.y]->getRank() != notstd::rank::FLAG))
			{
				cemetery[myRank][1]++;
				cemetery[13][1]++; //aumento fichas propias totales fuera del tablero
			}
			delete battlefield[opPosStatus.next.x][opPosStatus.next.y];
			battlefield[opPosStatus.next.x][opPosStatus.next.y] = battlefield[opPosStatus.previous.x][opPosStatus.previous.y];
			battlefield[opPosStatus.previous.x][opPosStatus.previous.y] = nullptr;
			aux = MY_TURN;
		}
		else if (r == myRank) //empate
		{
			if ((battlefield[opPosStatus.next.x][opPosStatus.next.y]->getRank() != notstd::rank::BOMB) && (battlefield[opPosStatus.next.x][opPosStatus.next.y]->getRank() != notstd::rank::FLAG))
			{
				cemetery[myRank][1]++;
				cemetery[13][1]++; //aumento fichas propias totales fuera del tablero
			}
			delete battlefield[opPosStatus.next.x][opPosStatus.next.y];
			delete battlefield[opPosStatus.previous.x][opPosStatus.previous.y];
			battlefield[opPosStatus.previous.x][opPosStatus.previous.y] = nullptr;
			battlefield[opPosStatus.next.x][opPosStatus.next.y] = nullptr;
			aux = MY_TURN;
		}
		else //gane
		{
			delete battlefield[opPosStatus.previous.x][opPosStatus.previous.y];
			battlefield[opPosStatus.previous.x][opPosStatus.previous.y] = nullptr;
		}
	}
	NotifyAllObservers();
	if (aux != state)
	{
		setState(aux);
	}
}

bool GameModel::isCemeteryEmpty()
{
	if (cemetery[12][1] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameModel::isRankCemeterySelected(notstd::rank r)
{
	if (cemetery[r][2]) //si esta seleccionado devuelve 1, si no 0 (cero).
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameModel::isAttackResolved()const
{
	return attackResolved;
}

bool GameModel::setFicha(notstd::rank r, pos currpos)
{
	if ((cemetery[r][1] > 0)&&(r <= 11)&&(battlefield[currpos.x][currpos.y] == nullptr))
	{
		cemetery[r][1]--;
		cemetery[12][1]--;
		battlefield[currpos.x][currpos.y] = new ficha(r);
		NotifyAllObservers();
		return true;
	}
	else
	{
		return false;
	}
}

notstd::rank GameModel::getMyRank()const
{
	return myRank;
}

void GameModel::selectFicha(pos p)
{
	battlefield[p.x][p.y]->select();
	NotifyAllObservers();
}

void GameModel::unselectFicha(pos p)
{
	battlefield[p.x][p.y]->unselect();
	NotifyAllObservers();
}

void GameModel::toggleFicha(pos p)
{
	battlefield[p.x][p.y]->toggleSelect();
	NotifyAllObservers();
}

void GameModel::selectRankCemetery(notstd::rank r)
{
	cemetery[r][2] = 1;  //seleccion de el rango requerido
	NotifyAllObservers();
}

void GameModel::unselectRankCemetery(notstd::rank r)
{
	cemetery[r][2] = 0;
	NotifyAllObservers();
}

void GameModel::unselectAllExcepetOneRankCemetery(notstd::rank r)
{
	for (int i = 0; i < TIPOS_DE_RANK; i++)
	{
		if (i != r)
		{
			unselectRankCemetery((notstd::rank)i);
		}
	}
	NotifyAllObservers();
}

void GameModel::unselectAllCemetery(void)
{
	for (int i = 0; i < TIPOS_DE_RANK; i++)
	{
		unselectRankCemetery((notstd::rank)i);
	}
	NotifyAllObservers();
}

void GameModel::unselectAllBattlefield(void)
{
	pos p(0,0);
	for (int i = 0; i < 10; i++)
	{
		p.x = i;
		for (int j = 0; j < 10; j++)
		{
			p.y = j;
			if (battlefield[p.x][p.y] != nullptr)
			{
				if ((battlefield[p.x][p.y]->getRank() != OTHERS)&& (battlefield[p.x][p.y]->getRank() != WATER))
				{
					battlefield[p.x][p.y]->unselect();
				}
			}
		}
	}
	NotifyAllObservers();
}

void GameModel::toggleSelectRankCemetery(notstd::rank r)
{
	cemetery[r][2] = (!cemetery[r][2]);
	NotifyAllObservers();
}

void GameModel::setFichasPlacedTrue()
{
	fichasPlaced = true;
	//NotifyAllObservers();
}

void GameModel::setFichasPlacedFalse()
{
	fichasPlaced = false;
	//NotifyAllObservers();
}

bool GameModel::getFichasPlaced()
{
	return fichasPlaced;
}

void GameModel::reset()
{
	//inicializacion del juego
	gameOver = false;

	Exit = false;

	moveDone = false;
	fichasPlaced = false;
	won = false;
	attackResolved = false;
	red = (!red); //cambio de color
	message = " ";

	//inicializaciondel battlefield

	for (int i = 0; i<FILAS; i++)
	{
		for (int j = 0; j<COLUMNAS; j++)
		{
			battlefield[i][j] = nullptr;
		}
	}
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<COLUMNAS; j++)
		{
			battlefield[i][j] = new ficha(OTHERS);
		}
	}
	for (int i = 4; i<6; i++)
	{
		for (int j = 2; j<4; j++)
		{
			battlefield[i][j] = new ficha(WATER);
		}
	}
	for (int i = 4; i<6; i++)
	{
		for (int j = 6; j<8; j++)
		{
			battlefield[i][j] = new ficha(WATER);
		}
	}
	//inicializacion de cemetery
	for (int i = 0; i<TIPOS_DE_RANK; i++)
	{
		cemetery[i][0] = (MARSHAL + i); //rango que representa una fila
		cemetery[i][2] = 0;  // las fichas comienzan desseleccionadas. si se seleccionan, se setean con un '1'
	}
	cemetery[TIPOS_DE_RANK + 1][0] = -1; //celda vacia sin info util
										 //cantidad de fichas por cada rango
	cemetery[MARSHAL][1] = 1;
	cemetery[GENERAL][1] = 1;
	cemetery[CORONEL][1] = 2;
	cemetery[MAJOR][1] = 3;
	cemetery[CAPTAIN][1] = 4;
	cemetery[LIEUTENANT][1] = 4;
	cemetery[SERGEANT][1] = 4;
	cemetery[MINER][1] = 5;
	cemetery[SCOUT][1] = 8;
	cemetery[SPY][1] = 1;
	cemetery[BOMB][1] = 6;
	cemetery[FLAG][1] = 1;
	cemetery[12][1] = 40; //total de fichas

						  //inicializacion del state
	setState(PLACING_FICHAS);
	timeRemaining = 120; // El jugador tiene 120 segundos para decidir antes de perder.
	rescuesRemaining = 2;
	repeatMoveCounter = 0;

	NotifyAllObservers();
}

button * GameModel::getButtonReference(int index)
{
	for (unsigned int i = 0; i < botones.size(); i++)
	{
		if (index == botones[i].getIndex())
		{
			return &botones[i];
		}
	}
	return nullptr;
}

notstd::rank GameModel::getRankFromPos(pos currpos) //asume que el rango ya fue validado
{
	if (battlefield[currpos.x][currpos.y] == nullptr)
	{
		return LAND;
	}
	else
	{
		return battlefield[currpos.x][currpos.y]->getRank();
	}
}

unsigned int GameModel::getNumberInCemetery(notstd::rank r)
{
	return cemetery[r][1];
}

int GameModel::getMaxOffsetFromPos(pos currpos)
{
	if (battlefield[currpos.x][currpos.y] == nullptr)
	{
		return 0;
	}
	else
	{
		return battlefield[currpos.x][currpos.y]->getMaxOffset ();
	}
	return 0;
}

bool GameModel::isSelectedFromPos(pos currpos)
{
	if (battlefield[currpos.x][currpos.y] == nullptr)
	{
		return false;
	}
	else
	{
		return battlefield[currpos.x][currpos.y]->isSelected();
	}
}

int GameModel::getTime()const
{
	return timeRemaining;
}

void GameModel::decrementTime()
{
	if (timeRemaining > 0)
	{
		timeRemaining--;
	}
	NotifyAllObservers();
}

void GameModel::restartTimer()
{
	timeRemaining = 120;
	//NotifyAllObservers();
}

bool GameModel::getMoveDone()
{
	return moveDone;
}

void GameModel::setMoveDoneTrue()
{
	moveDone = true;
	//NotifyAllObservers();
}

void GameModel::setMoveDoneFalse()
{
	moveDone = false;
	//NotifyAllObservers();
}

void GameModel::setMute(bool state)
{
	mute = state;
	NotifyAllObservers();
}

currStatus GameModel::GetmyPosStatus() const
{
	return myPosStatus;
}

currStatus GameModel::GetopPosStatus() const
{
	return opPosStatus;
}

void GameModel::playerWon()
{
	won = true;
	NotifyAllObservers();
}

bool GameModel::didPlayerWin()
{
	return won;
}

bool GameModel::verifyMovement()
{
	for (int i =0;i<10;i++)
	{
		for (int j =0;j<10;j++ )
		{
			if ((battlefield[i][j] != nullptr) && (battlefield[i][j]->getRank() != WATER) && (battlefield[i][j]->getRank() != BOMB)
				&& (battlefield[i][j]->getRank() != FLAG) && (battlefield[i][j]->getRank() != OTHERS))
			{
				if (clearSurroundings(i,j))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool GameModel::clearSurroundings(int i, int j)
{ 
		if ((i != 9)&&((battlefield[i+1][j] == nullptr)||(battlefield[i][j]->getRank() == OTHERS))) //hago uso de la naturaleza lazy del && para descartar los
		{																							//casos que quedan fuera de la matriz
			return true;
		}
		else if ((i != 0) && ((battlefield[i -1][j] == nullptr) || (battlefield[i][j]->getRank() == OTHERS)))
		{
			return true;
		}
		else if ((j != 9) && ((battlefield[i][j+1] == nullptr) || (battlefield[i][j]->getRank() == OTHERS)))
		{
			return true;
		}
		else if ((j !=0) && ((battlefield[i][j-1] == nullptr) || (battlefield[i][j]->getRank() == OTHERS)))
		{
			return true;
		}
		else
		{
			return false;
		}
}


void GameModel::swap(pos init, pos final)
{
	ficha * ptrAux = battlefield[final.x][final.y];
	battlefield[final.x][final.y] = battlefield[init.x][init.y];
	battlefield[init.x][init.y] = ptrAux;
	NotifyAllObservers();
}

void GameModel::printBattlefield()
{
	for (int i = 0; i<FILAS; i++)
	{
		for (int j = 0; j<COLUMNAS; j++)
		{
			if (battlefield[i][j] == nullptr)
			{
				std::cout << notstd::rank::LAND<< " ";
			}
			else
			{
				std::cout << battlefield[i][j]->getRank() << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool GameModel::isMuteOn()const
{
	return mute;
}

notstd::rank GameModel::getOpponentRank()const
{
	return opRank;
}

bool GameModel::verifyRescue()
{
	if (rescuesRemaining == 0)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if ((battlefield[0][i] != nullptr)&& (battlefield[0][i]->canItRescue())
				&& !(battlefield[0][i]->hasItRescued()))	//si la ficha puede rescatar y no rescato 
			{												// anteriormente, es apta
				rescuesRemaining--;
				battlefield[0][i]->rescue();
				return true;
			}
		}
	}
	return false;
}

bool GameModel::checkMoveRepetead(pos prev, pos next)
{
	if ((prev == myPosStatus.next)&&(next == myPosStatus.previous))
	{
		if (repeatMoveCounter == MAX_CANT_MOVEMENTS_REPETEAD)
		{
			return true;
		} 
		else
		{
			repeatMoveCounter++;
			return false;
		}
	}
	else
	{
		repeatMoveCounter = 0;
		return false;
	}
}

GameModel::~GameModel()
{
	//delete de todas las fichas que sobrevivieron en la matriz
	for (int i = 0; i<COLUMNAS; i++)
	{
		for (int j = 0; j<FILAS; j++)
		{
			if (battlefield[i][j] != nullptr)
			{
				delete battlefield[i][j];
			}
		}
	}
}

void GameModel::pushButton(button b)
{
	botones.push_back(b);
}

void GameModel::deleteButtons()
{
	botones.clear();
}

void GameModel::toggleMute(void)
{
	mute = !mute;
	NotifyAllObservers();
}

void GameModel::randomPos(void)
{
	srand(time(NULL));
	
	int counter = 0;
	pos randPos;
		
	if(!isCemeteryEmpty())
	{
		int max_counter = cemetery[TIPOS_DE_RANK][1];		//veo cuantas fichas debo colocar
		notstd::rank randomToken;

		while (counter < max_counter)
		{
			randomToken = (notstd::rank) (rand() % TIPOS_DE_RANK);			//tomo un rank al azar
			if (getNumberInCemetery(randomToken) > 0)			//veo si hay fichas con ese rank que faltan poner
			{
				do
				{
					randPos.x = 6 + (rand() % 4);		//tomo posiciones al azar del mapa en las que
					randPos.y = (rand() % 10);			//puedo colocar mis fichas
				} while (!setFicha(randomToken, randPos));

				counter++;
			}
		}
	}
	else
	{
		pos randPosDestiny;
		int max_moves = 65 + (rand() % 36);	//tomo un numero al azar de cambios a realizar entre 65 y 100

		for (counter = 0; counter < max_moves; counter++)
		{
			randPos.x = 6 + (rand() % 4);
			randPos.y = (rand() % 10);

			randPosDestiny.x = 6 + (rand() % 4);
			randPosDestiny.y = (rand() % 10);
		
			swap(randPos, randPosDestiny);
		}
	}
}

bool GameModel::updateLeaderboard(std::string& winner)
{
	bool succes = false;

	fstream leaderboard(LEADERBOARDDIR);

	if (leaderboard.good())
	{
		int charFromLeader;
		string stringLeader;

		for (int i = 0; (charFromLeader = leaderboard.get()) != EOF; i++)		//Copio el archivo original en un string
		{
			stringLeader.resize(i + 1);
			stringLeader[i] = charFromLeader;
		}

		leaderboard.close();

		ofstream newleaderboard(LEADERBOARDDIR);			//Abro un nuevo archivo donde guardar el nuevo leaderbord

		if (newleaderboard.good())
		{
			int pos = stringLeader.find(winner, 0);		//Busco si se encuentra el ganador (en caso de no encontrarse)
														//find devuelve int = npos

			if (pos != string::npos)
			{
				string score;

				int scorePos = stringLeader.find(' ', pos) + 1;

				for (int k = 0; (stringLeader[scorePos + k] != '\n') && ((k + scorePos) < stringLeader.size()); k++)		//Tomo el string del puntaje
				{
					score.resize(k + 1);
					score[k] = stringLeader[scorePos + k];
				}

				int newScore = stringToInt(score) + 1;			//Incrementeo el numero de vece que gano
				score = intToString(newScore);					//Paso el valor a string

				string numberStringCmp;				//String para comparar com mi puntaje
				int numberValueCmp;					//Varaible para guardar el puntaje a comparar en int 

				int initNum;						//Variables necesarias para determinar la posicion
				int endNum;							//donde se guardara el nuevo string
				int prevEndNum = 0;

				bool finded = false;

				for (initNum = 0, endNum = 0; !finded; endNum++)
				{
					initNum = stringLeader.find(' ', initNum) + 1;
					endNum = stringLeader.find('\n', initNum);

					for (int k = 0; k + initNum < endNum; k++)		//tomo los numeros de cada jugador
					{
						numberStringCmp.resize(k + 1);
						numberStringCmp[k] = stringLeader[initNum + k];
					}

					numberValueCmp = stringToInt(numberStringCmp);

					if (newScore >= numberValueCmp)
					{
						finded = true;		//si es mayor, coloco mi puntaje en la linea anterior
					}
					else
					{
						prevEndNum = endNum;
					}
				}

				stringLeader.erase(pos, winner.size() + score.size() + 2);		//Borro winner con puntaje anterior

				if (prevEndNum == 0)
				{
					stringLeader.insert(0, winner + ' ' + score + '\n');		//caso en el que el leaderboard esta vacio
																				//no hay un \n antes del nombre de winner
				}
				else
				{
					stringLeader.insert(prevEndNum + 1, winner + ' ' + score + '\n');
				}

				for (int count = 0; count < stringLeader.size(); count++)		//Transcribo el nuevo leaderboard
				{
					newleaderboard << stringLeader[count];
					newleaderboard.flush();
				}

				succes = true;
			}
			else
			{
				newleaderboard << stringLeader;				//Agrego al final el nuevo puntaje
				newleaderboard << winner + " 1" + '\n';
				newleaderboard.flush();
				succes = true;
			}
		}
		newleaderboard.close();
	}
	else
	{
		leaderboard.open(LEADERBOARDDIR, fstream::out);
		leaderboard << winner + " 1" + '\n';
		leaderboard.flush();
		succes = true;
	}

	return succes;
}

string GameModel::intToString(unsigned int number)
{
	int number_ = number;
	int digitos;
	for (digitos = 1; (number_ /= 10) > 0; digitos++);			//cuento la cantidad de digitos

	string stringNumber;
	stringNumber.resize(digitos);

	int auxNumber;

	number_ = number;

	for (int i = 0; i < digitos; i++) {
		auxNumber = number_ % 10;
		number_ = number_ / 10;
		stringNumber[digitos - 1 - i] = '0' + auxNumber;
	}

	return stringNumber;
}

unsigned int GameModel::stringToInt(string number)
{
	unsigned int value = 0;

	for (int i = 0; i < number.size(); i++)
	{
		if (((number[i] - '0') >= 0) && ((number[i] - '0') <= 9))
			value = value * 10 + (number[i] - '0');
	}
	return value;
}