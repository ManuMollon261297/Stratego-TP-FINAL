#pragma once
#include "GameState.h"
class PlacingFichas: public gameState
{
public:
	PlacingFichas();
	virtual ~PlacingFichas();
	virtual gameState* OnSoldier(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnCemetery(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnOponent(MouseInfo & ev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnLand(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnWater(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnConfirmPlaces(GameModel * p2GameModel, MouseStates & Mstate);
	virtual gameState* OnRand(GameModel* p2GameModel);
};

