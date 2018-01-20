#pragma once
#include "GameState.h"
class PlacingFichas: public gameState
{
public:
	PlacingFichas();
	virtual ~PlacingFichas();
	virtual gameState* OnSoldier(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnCemetery(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnOponent(MouseEvent & ev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnLand(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnWater(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnConfirmPlaces(GameModel * p2GameModel);
};

