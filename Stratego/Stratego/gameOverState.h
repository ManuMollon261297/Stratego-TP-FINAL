#pragma once
#include "GameState.h"
class gameOverState: public gameState
{
public:
	gameOverState();
	virtual gameState* OnPlayAgain(GameModel * p2GameModel);
	virtual gameState* OnGameOver(GameModel * p2GameModel);
	~gameOverState();
};

