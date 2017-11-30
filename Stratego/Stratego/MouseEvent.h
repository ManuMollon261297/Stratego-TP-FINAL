#pragma once
#include "pos.h"

enum sectors { FRIENDLY_BATTLEFIELD, HOSTIL_BATTLEFIELD, NEUTRAL_BATTLEFIELD, CEMETERY_SECTOR, INVALID_SECTOR };
enum Mevents { SOLDIER_EV, OPONENT_EV, LAND_EV, WATER_EV, CEMETERY_EV, NO_EVENT };

typedef struct
{
	Mevents type;
	pos evPos;
	sectors sector;
	rank r;
} MouseEvent;