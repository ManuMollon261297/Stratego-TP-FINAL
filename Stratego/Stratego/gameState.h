#pragma once
#include "mouseGameController.h"

enum states { MY_TURN, OP_TURN, MY_ATTACKING, OP_ATTACKING, MY_MOVING, OP_MOVING, PLACING_FICHAS, GAME_OVER, IDLE
		,ENDING_PLACING_FICHAS, WAITING_FOR_OPPONENTS_SELECTION, PLAY_AGAIN_SELECTED, GAME_OVER_SELECTED };

class gameState
{
public:
	gameState();
	virtual ~gameState();						//rutinas de accion ante un evento
	virtual gameState* OnSoldier(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);          
	virtual gameState* OnCemetery(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnOponent(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnLand(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnWater(MouseEvent & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnConfirmPlaces(GameModel * p2GameModel);
	virtual gameState* OnPlayAgain(GameModel * p2GameModel);
	virtual gameState* OnGameOver(GameModel * p2GameModel);
	virtual int getState();

protected:
	int state;
};

