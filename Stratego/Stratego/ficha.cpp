#include "ficha.h"



ficha::ficha(rank rango_)
{
	fichaRank = rango_;
	hasRescued = 0;
	switch (rango_)
	{
	case MARSHAL:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case GENERAL:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case COLONEL:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case MAJOR:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case CAPTAIN:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case LIEUTENANT:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case SERGEANT:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case MINER:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case SCOUT:
		maxOffset = 10;
		canRescue = false;
		canBeRescued = true;
		break;
	case SPY:
		maxOffset = 1;
		canRescue = true;
		canBeRescued = true;
		break;
	case BOMB:
		maxOffset = 0;
		canRescue = false;
		canBeRescued = false;
		break;
	case FLAG:
		maxOffset = 0;
		canRescue = false;
		canBeRescued = false;
		break;
	case WATER:
		maxOffset = 0;
		canRescue = false;
		canBeRescued = false;
		break;
	case OTHERS:
		maxOffset = 10;
		canRescue = false;
		canBeRescued = false;
		break;
	case LAND:
		maxOffset = 0;
		canRescue = false;
		canBeRescued = false;
		break;
	}
}


ficha::~ficha()
{
	//do nothing
}

rank ficha::getRank()
{
	return fichaRank;
}

int ficha::getMaxOffset()
{
	return maxOffset;
}

bool ficha::canItRescue()
{
	return canRescue;
}

bool ficha::canItBeRescued()
{
	return canBeRescued;
}

bool ficha::hasItRescued()
{
	return hasRescued;
}

bool ficha::isSelected()
{
	return selected;
}

void ficha::rescue()
{
	hasRescued = true;
}

void ficha::select()
{
	selected = true;
}

void ficha::unselect()
{
	selected = false;
}

void ficha::toggleSelect()
{
	selected = (!selected);
}
