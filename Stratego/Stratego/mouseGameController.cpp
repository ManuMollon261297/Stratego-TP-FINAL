#include "mouseGameController.h"
#include "gameState.h"
#include "IdleState.h"
#include "MyMoving.h"
#include "OpMoving.h"
#include "MyTurn.h"
#include "OpTurn.h"
#include "PlacingFichas.h"
#include "finishingPlacing.h"
#include "MyAttacking.h"
#include "OpAttacking.h"
#include "gameOverState.h"


#define IS_CEMETERY_TOUCHED(x, y) ( ((x > MARGEN_X_CEMETERY) && (x < (MARGEN_X_CEMETERY + SIZE_CEMETERY_X))) && ((y > MARGEN_Y_CEMETERY) && (y < (MARGEN_Y_CEMETERY + SIZE_CEMETERY_Y))) )
#define IS_BATTLEFIELD_TOUCHED(x, y) ( ((x > MARGEN_X_BATTLEFIELD) && (x < (MARGEN_X_BATTLEFIELD + SIZE_BATTLEFIELD_X))) && ((y > MARGEN_Y_BATTLEFIELD) && (y < (MARGEN_Y_BATTLEFIELD + SIZE_BATTLEFIELD_Y))) )
#define IS_FRIENDLY_BATTLEFIELD_TOUCHED(x, y) ( ((x > MARGEN_X_BATTLEFIELD) && (x < (MARGEN_X_BATTLEFIELD + SIZE_BATTLEFIELD_X))) && ((y > MARGEN_Y_BATTLEFIELD + SIZE_BATTLEFIELD_Y - (4 * SIZE_CASILLERO_Y)) && (y < (MARGEN_Y_BATTLEFIELD + SIZE_BATTLEFIELD_Y))) )
#define IS_HOSTIL_BATTLEFIELD_TOUCHED(x, y) ( ((x > MARGEN_X_BATTLEFIELD) && (x < (MARGEN_X_BATTLEFIELD + SIZE_BATTLEFIELD_X))) && ((y > MARGEN_Y_BATTLEFIELD) && (y < (MARGEN_Y_BATTLEFIELD + (4 * SIZE_CASILLERO_Y)))) )

mouseGameController::mouseGameController()
{
	estadoModel = new IdleState; //debe ser un iddle state
	Mstate = NONE_SELECTED;
}

GameModel * mouseGameController::getP2model()
{
	return p2gameModel;
}

void mouseGameController::saveEvent(MouseEvent & Mev)
{
	memoryEv = Mev;
}

MouseEvent & mouseGameController::getPreviousEvent()
{
	return memoryEv;
}

bool mouseGameController::isEqualToPrevious(MouseEvent & Mev)
{
	bool ret;
	if ((memoryEv.r == Mev.r) && (memoryEv.evPos == Mev.evPos))
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}



MouseEvent mouseGameController::shape(double x, double y)
{
	MouseEvent Mev;
	Mev.sector = getSectorTouched(x, y);
	switch (Mev.sector)
	{
		case FRIENDLY_BATTLEFIELD:
		case HOSTIL_BATTLEFIELD:
		case NEUTRAL_BATTLEFIELD:
			Mev.evPos = translateBattlefieldCoords(x, y);
			Mev.type = fetchMevType(Mev.evPos);
			Mev.r = fetchMevRank(Mev.evPos);
			break;
		case CEMETERY_SECTOR:
			Mev.evPos = translateCemeteryCoords(x, y);
			Mev.r = fetchMevRankFromCemetery(Mev.evPos.y);
			Mev.type = CEMETERY_EV;
			break;
		case INVALID_SECTOR:
			Mev.evPos = { -1, -1 };
			Mev.type = NO_EVENT;
			break;
	}

	return Mev;
}

void mouseGameController::dispatch(MouseEvent Mev)
{
	updateControllerState(p2gameModel->getState());
	gameState * proximoEstado = nullptr;
	switch (Mev.type)
	{
		case NO_EVENT:
			break;
		case SOLDIER_EV:
			proximoEstado = estadoModel->OnSoldier(Mev, Mstate, this, p2gameModel);
			break;
		case OPONENT_EV:
			proximoEstado = estadoModel->OnOponent(Mev, Mstate, this, p2gameModel);
			break;
		case LAND_EV:
			proximoEstado = estadoModel->OnLand(Mev, Mstate, this, p2gameModel);
			break;
		case WATER_EV:
			proximoEstado = estadoModel->OnWater(Mev, Mstate, this, p2gameModel);
			break;
		case CEMETERY_EV:
			proximoEstado = estadoModel->OnCemetery(Mev, Mstate, this, p2gameModel);
			break;
	}
	
	if (proximoEstado != nullptr) //hubo cambio de estado
	{
		delete estadoModel;
		estadoModel = proximoEstado;
		proximoEstado = nullptr;
		updateModelState();
	}
}

sectors mouseGameController::getSectorTouched(double x, double y)
{
	sectors sectorRet;

	if (IS_CEMETERY_TOUCHED(x, y))
	{
		sectorRet = CEMETERY_SECTOR;
	}
	else if (IS_BATTLEFIELD_TOUCHED(x, y))
	{
		if (IS_FRIENDLY_BATTLEFIELD_TOUCHED(x, y))
		{
			sectorRet = FRIENDLY_BATTLEFIELD;
		}
		else if (IS_HOSTIL_BATTLEFIELD_TOUCHED(x, y))
		{
			sectorRet = HOSTIL_BATTLEFIELD;
		}
		else
		{
			sectorRet = NEUTRAL_BATTLEFIELD;
		}
	}
	else
	{
		sectorRet = INVALID_SECTOR;
	}

	return sectorRet;
}

pos mouseGameController::translateBattlefieldCoords(double x, double y)
{
	pos ret;

	ret.x = (int) ((x - MARGEN_X_BATTLEFIELD) / SIZE_CASILLERO_X);  //devuelve coordenada entera entre 0 y la cantidad de columnas -1
	ret.y = (int) ((y - MARGEN_Y_BATTLEFIELD) / SIZE_CASILLERO_Y);  //devuelve coordenada entera entre 0 y la cantidad de filas -1

	return ret;
}

pos mouseGameController::translateCemeteryCoords(double x, double y)
{
	pos ret;

	ret.x = -1; //pos.x siempre se setea en -1
	ret.y = (int)((y - MARGEN_Y_CEMETERY) / SIZE_CASILLERO_Y);

	return ret;
}

rank mouseGameController::fetchMevRank(pos p)
{
	return (p2gameModel->getRankFromPos(p));
}

rank mouseGameController::fetchMevRankFromCemetery(int y)
{
	rank r;
	switch (y)
	{
	case 0: r = MARSHAL; break;
	case 1: r = GENERAL; break;
	case 2: r = CORONEL; break;
	case 3: r = MAJOR; break;
	case 4: r = CAPTAIN; break;
	case 5: r = LIEUTENANT; break;
	case 6: r = SERGEANT; break;
	case 7: r = MINER; break;
	case 8: r = SCOUT; break;
	case 9: r = SPY; break;
	case 10: r = BOMB; break;
	case 11: r = FLAG; break;
	case 12: r = WATER; break;
	case 13: r = OTHERS; break;
	case 14: r = LAND; break;
	}
	return r;
}

Mevents mouseGameController::fetchMevType(pos pos_)
{
	Mevents ret;
	rank rank_ = p2gameModel->getRankFromPos(pos_);
	if (rank_ == LAND)
	{
		ret = LAND_EV;
	}
	else if (rank_ == WATER)
	{
		ret = WATER_EV;
	}
	else if (rank_ == OTHERS)
	{
		ret = OPONENT_EV;
	}
	else
	{
		ret = SOLDIER_EV;
	}

	return ret;
}

bool mouseGameController::fetchObstacle(int fijoOri, int movilOri, int fijoDest, int varDest, char c_recorrido)
{
	bool ret = true;
	int potentialObstacles = 0;
	pos recorrido;
	if (c_recorrido == 'y')
	{
		recorrido.x = fijoOri;
		recorrido.y = movilOri;
		if ((movilOri) > (varDest)) //se mueve para atras
		{
			potentialObstacles = movilOri - varDest - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.y = movilOri - i;  //recorre hacia atras
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
		else //se mueve para adelante
		{
			potentialObstacles = varDest - movilOri - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.y = (memoryEv.evPos.y) + i;  //recorre hacia adelante
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
	}
	else if (c_recorrido == 'x')
	{
		recorrido.y = fijoOri;
		recorrido.x = movilOri;
		if ((movilOri) > (varDest)) //se mueve para atras
		{
			potentialObstacles = movilOri - varDest - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.x = movilOri - i;  //recorre hacia atras
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
		else //se mueve para adelante
		{
			potentialObstacles = varDest - movilOri - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.x = (memoryEv.evPos.y) + i;  //recorre hacia adelante
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
	}

	
	

	return !ret; //devuelve true si hubo obstaculo, false si  en el medio solo hay LAND
}

void mouseGameController::updateControllerState(int modelState)
{
	if ((estadoModel != nullptr) && (p2gameModel->getState() != estadoModel->getState()))
	{
		delete estadoModel;
		switch (p2gameModel->getState())
		{
			case MY_TURN:
				estadoModel = new MyTurn;
				break;
			case OP_TURN:
				estadoModel = new OpTurn;
				break;
			case MY_ATTACKING:
				estadoModel = new MyAttacking;
				break;
			case OP_ATTACKING:
				estadoModel = new OpAttacking;
				break;
			case MY_MOVING:
				estadoModel = new MyMoving;
				break;
			case OP_MOVING:
				estadoModel = new OpMoving;
				break;
			case PLACING_FICHAS:
				estadoModel = new PlacingFichas;
				break;
			case IDLE:
				estadoModel = new IdleState;
				break;
			case GAME_OVER:
				estadoModel = new gameOverState;
				break;
		}
	}
}

void mouseGameController::updateModelState()
{
	p2gameModel->setState(estadoModel->getState());
}

bool mouseGameController::validOffsetMovement(pos destiny)
{
	bool ret= false;
	int offset = 0;
	if (((memoryEv.evPos.x) == (destiny.x)) || ((memoryEv.evPos.y) == (destiny.y)))
	{
		if ((memoryEv.evPos.x) == (destiny.x))
		{
			offset = ((memoryEv.evPos.y > destiny.y) ? (memoryEv.evPos.y - destiny.y) : (destiny.y - memoryEv.evPos.y));
			if (offset <= p2gameModel->getRankFromPos(memoryEv.evPos))
			{
				ret = true;
			}
		}
		else
		{
			offset = ((memoryEv.evPos.x > destiny.x) ? (memoryEv.evPos.x - destiny.x) : (destiny.x - memoryEv.evPos.x));
			if (offset <= p2gameModel->getRankFromPos(memoryEv.evPos))
			{
				ret = true;
			}
		}
	}
	
	return ret;
}

bool mouseGameController::validObstacles(pos destiny)  //debe llamarse luego de validOffset, sino no sirve
{
	bool ret = false;
	if ((memoryEv.evPos.x) == (destiny.x)) //se mueve en 'y', en 'x' queda fijo
	{
		ret = !fetchObstacle(memoryEv.evPos.x, memoryEv.evPos.y, destiny.x, destiny.y, 'y');
	}
	else //se mueve en 'x', en 'y' queda fijo.
	{
		ret = !fetchObstacle(memoryEv.evPos.y, memoryEv.evPos.x, destiny.y, destiny.x, 'x');
	}
	

	return ret;
}


mouseGameController::~mouseGameController()
{
	delete estadoModel;
}
