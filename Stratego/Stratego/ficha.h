#pragma once
#include "ranks.h"

using namespace notstd;

class ficha
{
public:
	ficha(notstd::rank rango_);
	~ficha();
	//getters
	notstd::rank getRank();
	int getMaxOffset();
	bool canItRescue();
	bool canItBeRescued();
	bool hasItRescued();
	bool isSelected();
	void rescue();
	void select();
	void unselect();
	void toggleSelect();

private:
	notstd::rank fichaRank;
	int maxOffset;
	bool canRescue;
	bool canBeRescued;
	bool hasRescued;
	bool selected;
};

