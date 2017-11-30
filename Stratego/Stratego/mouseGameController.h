#pragma once
#include "GameModel.h"

//dimensiones
#define CANT_CASILLEROS_X 10
#define CANT_CASILLEROS_Y 10
#define SIZE_BATTLEFIELD_X 800
#define SIZE_BATTLEFIELD_Y 800
#define SIZE_CASILLERO_X SIZE_BATTLEFIELD_X / CANT_CASILLEROS_X
#define SIZE_CASILLERO_Y SIZE_BATTLEFIELD_Y / CANT_CASILLEROS_Y
#define SIZE_CEMETERY_X SIZE_CASILLERO_X
#define SIZE_CEMETERY_Y SIZE_BATTLEFIELD_Y
#define MARGEN_X_CEMETERY SIZE_CASILLERO_X
#define MARGEN_Y_CEMETERY SIZE_CASILLERO_Y
#define MARGEN_X_BATTLEFIELD MARGEN_X_CEMETERY + SIZE_CEMETERY_X + SIZE_CASILLERO_X //cemetery a la izquierda de battlefield
#define MARGEN_Y_BATTLEFIELD SIZE_CASILLERO_Y

//sectores

enum sectors {FRIENDLY_BATTLEFIELD, HOSTIL_BATTLEFIELD, NEUTRAL_BATTLEFIELD, CEMETERY_SECTOR, INVALID_SECTOR};

enum Mevents { SOLDIER_EV, OPONENT_EV, LAND_EV, WATER_EV, CEMETERY_EV, NO_EVENT };

typedef struct
{
	Mevents type;
	pos evPos;
	sectors sector;
} MouseEvent;

class mouseGameController
{
public:
	mouseGameController();

	~mouseGameController();
private:
	GameModel * p2gameModel;
	MouseEvent Mev;

	void shape(double x, double y); //devuelve un evento de mouse (SOLDADO, CEMETERY, LAND, RIVAL, NO_EVENT)

	sectors getSectorTouched(double x, double y);

	pos translateBattlefieldCoords(double x, double y);
	pos translateCemeteryCoords(double x, double y); //en pos.y se devuelve el indice correspondiente del arreglo de cemetery. 
															//En pos.x siempre se devuelve 0 (cero).
	
	Mevents fetchMevType(pos pos_);

};

