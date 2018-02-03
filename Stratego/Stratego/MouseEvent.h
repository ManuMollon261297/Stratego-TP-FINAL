#pragma once
#include "pos.h"
#include "ranks.h"

enum sectors { FRIENDLY_BATTLEFIELD, HOSTIL_BATTLEFIELD, NEUTRAL_BATTLEFIELD, CEMETERY_SECTOR, BOTON_PLACE_READY, BOTON_PLAY_AGAIN, BOTON_GAME_OVER, INVALID_SECTOR };
enum Mevents { SOLDIER_EV, OPONENT_EV, LAND_EV, WATER_EV, CEMETERY_EV, BOTON_PLACE_READY_EV, NO_EVENT};

typedef struct
{
	Mevents type;
	pos evPos;
	sectors sector;
	rank r;
} MouseEvent;