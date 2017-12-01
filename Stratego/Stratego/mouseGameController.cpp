#include "mouseGameController.h"
#include "gameState.h"
#include "IdleState.h"
#include "MyMoving.h"
#include "OpMoving.h"
#include "MyTurn.h"
#include "OpTurn.h"
#include "PlacingFichas.h"

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

bool mouseGameController::validOffsetMovement(pos destiny)
{
	return false;
}

bool mouseGameController::validObstacles(pos destiny)
{
	return false;
}


mouseGameController::~mouseGameController()
{
	delete estadoModel;
}


//pos mouseGameController::getFirstSelection()
//{
//	return firstSelection;
//}
//
//pos mouseGameController::getSecondSelection()
//{
//	return secondSelection;
//}
//
//void mouseGameController::setFirstSelection(pos p)
//{
//	firstSelection = p;
//}
//
//void mouseGameController::setSecondSelection(pos p)
//{
//	secondSelection = p;
//}
//
//
//bool mouseGameController::areSelectionsEquals()
//{
//	bool ret;
//	if (firstSelection == secondSelection)
//	{
//		ret = true;
//	}
//	else
//	{
//		ret = false;
//	}
//	return ret;
//}