#pragma once
#include "ranks.h"
class ficha
{
public:
	ficha(rank rango_);
	~ficha();
	//getters
	rank getRank();
	int getMaxOffset();
	bool canItRescue();
	bool canItBeRescued();
	bool hasItRescued();
	void rescue();
	void select();
	void unselect();
	void toggleSelect();

private:
	rank fichaRank;
	int maxOffset;
	bool canRescue;
	bool canBeRescued;
	bool hasRescued;
	bool selected;
};

