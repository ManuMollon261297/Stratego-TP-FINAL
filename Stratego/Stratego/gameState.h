#pragma once
#include "mouseGameController.h"

class gameState
{
public:
	gameState();
	virtual ~gameState();						//rutinas de accion ante un evento
	virtual gameState* OnSoldier(MouseInfo& Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);          
	virtual gameState* OnCemetery(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnOponent(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnLand(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnWater(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel);
	virtual gameState* OnConfirmPlaces(GameModel * p2GameModel);
	virtual gameState* OnPlayAgain(GameModel * p2GameModel);
	virtual gameState* OnGameOver(GameModel * p2GameModel);
	virtual gameState* OnSound(GameModel * p2GameModel);
	virtual int getState();

protected:
	int state;
};

