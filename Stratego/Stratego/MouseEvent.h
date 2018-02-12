#pragma once
#include "pos.h"
#include "ranks.h"
#include "allegro5\allegro.h"
#include "Event.h"

enum sectors { FRIENDLY_BATTLEFIELD, HOSTIL_BATTLEFIELD, NEUTRAL_BATTLEFIELD, CEMETERY_SECTOR, BOTON_PLACE_READY, BOTON_PLAY_AGAIN, BOTON_GAME_OVER, BOMB_SECTOR, BOTON_SOUND, FLAG_SECTOR, INVALID_SECTOR };
enum Mevents { SOLDIER_EV, OPONENT_EV, LAND_EV, WATER_EV, CEMETERY_EV, BOTON_PLACE_READY_EV, BOTON_SOUND_EV, GAME_OVER_EV, PLAY_AGAIN_EV, NO_EVENT};

typedef struct
{
	Mevents type;
	pos evPos;
	sectors sector;
	notstd::rank r;
} MouseInfo;

class MouseEvent : public GenericEvent
{
public:
	MouseEvent(ALLEGRO_EVENT);
	int x;
	int y;
};