#include "mouseGameController.h"

#define IS_CEMETERY_TOUCHED(x, y) ( ((x > MARGEN_X_CEMETERY) && (x < (MARGEN_X_CEMETERY + SIZE_CEMETERY_X))) && ((y > MARGEN_Y_CEMETERY) && (y < (MARGEN_Y_CEMETERY + SIZE_CEMETERY_Y))) )
#define IS_BATTLEFIELD_TOUCHED(x, y) ( ((x > MARGEN_X_BATTLEFIELD) && (x < (MARGEN_X_BATTLEFIELD + SIZE_BATTLEFIELD_X))) && ((y > MARGEN_Y_BATTLEFIELD) && (y < (MARGEN_Y_BATTLEFIELD + SIZE_BATTLEFIELD_Y))) )
#define IS_FRIENDLY_BATTLEFIELD_TOUCHED(x, y) ( ((x > MARGEN_X_BATTLEFIELD) && (x < (MARGEN_X_BATTLEFIELD + SIZE_BATTLEFIELD_X))) && ((y > MARGEN_Y_BATTLEFIELD + SIZE_BATTLEFIELD_Y - (4 * SIZE_CASILLERO_Y)) && (y < (MARGEN_Y_BATTLEFIELD + SIZE_BATTLEFIELD_Y))) )
#define IS_HOSTIL_BATTLEFIELD_TOUCHED(x, y) ( ((x > MARGEN_X_BATTLEFIELD) && (x < (MARGEN_X_BATTLEFIELD + SIZE_BATTLEFIELD_X))) && ((y > MARGEN_Y_BATTLEFIELD) && (y < (MARGEN_Y_BATTLEFIELD + (4 * SIZE_CASILLERO_Y)))) )

mouseGameController::mouseGameController()
{

}


void mouseGameController::shape(double x, double y)
{
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

	ret.x = 0; //pos.x siempre se setea en cero (no se usa)
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
}
