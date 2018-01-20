#pragma once
#include "gameState.h"
class MyTurn: public gameState
{
public:
	MyTurn();
	virtual gameState* OnSoldier(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnCemetery(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnOponent(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnLand(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnWater(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	~MyTurn();
};

