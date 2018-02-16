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

	//inicializacion del battlefield

	for (int i = 0; i<FILAS; i++)
	{
		for (int j = 0; j<COLUMNAS; j++)
		{

			if (battlefield[i][j] != nullptr)
			{
				delete battlefield[i][j];
				battlefield[i][j] = nullptr;
			}
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
}

bool GameModel::getMoveDone()
{
	return moveDone;
}

void GameModel::setMoveDoneTrue()
{
	moveDone = true;
}

void GameModel::setMoveDoneFalse()
{
	moveDone = false;
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

bool GameModel::updateLeaderboard(const std::string& winner)
{
	std::fstream leaderboard(LEADERBOARDDIR);
	std::ofstream leaderboardI(LEADERBOARDDIR, std::ios_base::app | std::ios_base::out);

	bool found = false;
	bool auxFileCreated = false;

	if (leaderboard.is_open())
	{
		//busco si es un highscore
		std::vector<std::string> chart;
		std::string line;
		while (std::getline(leaderboard, line))
		{
			chart.push_back(line);
		}
		std::vector<std::string> names;
		names = chart;
		for (int i = 0; i<chart.size(); i++)
		{
			if (chart[i].size() != 0)
			{
				int j = (int) (chart[i].size() - 1);
				while ((chart[i][j] <= '9') && (chart[i][j] >= '0')) //mientras sea parte del puntaje
				{
					names[i].pop_back(); //me deshago del puntaje
					j--;
				}
				names[i].pop_back(); //me deshago del espacio
			}
		}
		//en name se encuentra el nomrbre sin el puntaje y en chart con el puntaje

		for (int i = 0; i<names.size(); i++)
		{
			if (names[i] == winner) //lo encontre en el leadeboard
			{
				//tengo que incrementralo y ver si esta en la posicion correcta
				found = true;
				char auxNumber;
				int newScore = 0; //aca cargo el nuevo puntaje del ganador
				int j = (int) (chart[i].size() - 1);
				int mult = 1;
				//cargo newScore
				while ((chart[i][j] <= '9') && (chart[i][j] >= '0')) //mientras sea parte del puntaje
				{
					auxNumber = chart[i][j] - '0';
					newScore += (auxNumber*mult);
					mult *= 10;
					j--;
				}
				newScore += 1;
				//paso newScore a string
				std::string scoreString = std::to_string(newScore);
				//creo un nuevo archivo
				std::ofstream auxFile("auxFile.txt");
				auxFileCreated = true;
				// voy copiando strings del viejo y agrego el nuevo !!!
				bool inserted = false;
				int auxScore;
				if (names.size() == 1)
				{
					auxFile << winner << ' ' << scoreString << std::endl; //nuevo puntaje
					inserted = true;
				}
				else
				{
					for (int k = 0; k< names.size(); k++)
					{
						auxScore = 0;
						int j = (int) (chart[k].size() - 1);
						int mult = 1;
						//cargo newScore
						while ((chart[k][j] <= '9') && (chart[k][j] >= '0')) //mientras sea parte del puntaje
						{
							auxNumber = chart[k][j] - '0';
							auxScore += (auxNumber*mult);
							mult *= 10;
							j--;
						}
						if (winner != names[k])
						{
							if ((newScore >= auxScore) && (inserted == false))
							{
								auxFile << winner << ' ' << scoreString << std::endl; //nuevo puntaje
								inserted = true;
							}
							auxFile << chart[k] << std::endl;
						}
					}
				}
				i = (int) names.size(); //lo fuerzo a salir del for si ya se encontro el nombre en el leaderboard
			}
		}
		if (found == false)
		{
			//no lo encontre en el archivo y lo tengo que agregar
			leaderboardI << winner << " 1" << std::endl;
		}
	}
	else
	{
		//creo el archivo y le pongo el ganador
		std::ofstream leaderboardAux(LEADERBOARDDIR);
		leaderboardAux << winner << " 1" << std::endl;
	}

	leaderboard.close();
	leaderboardI.close();
	if (auxFileCreated)
	{
		remove(LEADERBOARDDIR);
		rename("auxFile.txt", LEADERBOARDDIR);
	}

	return found;
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

bool GameModel::isAttackAdjacent(pos& ori, pos& des)const
{
	if (des.x == ori.x) //El ataque es sobre la misma fila.
	{
		if ((des.y == (ori.y - 1)) || (des.y == (ori.y + 1)))
		{
			return true; //Devuelve true si se ataco a la columna inmediamente superior
						//o inmediatamente inferior.
		}
		else
		{
			return false; //Sino el ataque no fue adyacente.
		}
	}
	else if (des.y == ori.y) //El ataque es sobre la misma columna.
	{
		if ((des.x == (ori.x - 1)) || (des.x == (ori.x + 1)))
		{
			return true; //Devuelve true si se ataco a la fila inmediamente superior
						 //o inmediatamente inferior.
		}
		else
		{
			return false; //Sino el ataque no fue adyacente.
		}
	}
	else //No es movimiento valido.
	{
		return false;
	}
}