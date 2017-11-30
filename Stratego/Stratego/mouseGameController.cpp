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

pos mouseGameController::getFirstSelection()
{
	return firstSelection;
}

pos mouseGameController::getSecondSelection()
{
	return secondSelection;
}

void mouseGameController::setFirstSelection(pos p)
{
	firstSelection = p;
}

void mouseGameController::setSecondSelection(pos p)
{
	secondSelection = p;
}


bool mouseGameController::areSelectionsEquals()
{
	bool ret;
	if (firstSelection == secondSelection)
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
			break;
		case CEMETERY_SECTOR:
			Mev.evPos = translateCemeteryCoords(x, y);
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
			proximoEstado = estadoModel->OnSoldier(&Mev, Mstate, this);
			break;
		case OPONENT_EV:
			proximoEstado = estadoModel->OnOponent(&Mev, Mstate, this);
			break;
		case LAND_EV:
			proximoEstado = estadoModel->OnLand(&Mev, Mstate, this);
			break;
		case WATER_EV:
			proximoEstado = estadoModel->OnWater(&Mev, Mstate, this);
			break;
		case CEMETERY_EV:
			proximoEstado = estadoModel->OnCemetery(&Mev, Mstate, this);
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


mouseGameController::~mouseGameController()
{
	delete estadoModel;
}
