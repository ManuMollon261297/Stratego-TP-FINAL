#pragma once
#include "MouseEvent.h"
#include "mouseGameController.h"

enum states { MY_TURN, OP_TURN, MY_ATTACKING, OP_ATTACKING, MY_MOVING, OP_MOVING, PLACING_FICHAS, GAME_OVER, IDLE, FINISHING_PLACING };

enum MouseStates { NONE_SELECTED, SOLDIER_SELECTED, CEMETERY_SELECTED };

class gameState
{
public:
	virtual ~gameState();						//rutinas de accion ante un evento
	virtual gameState* OnSoldier(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel);          
	virtual gameState* OnCemetery(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnOponent(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnLand(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnWater(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual int getState();

protected:
	int state;
};

