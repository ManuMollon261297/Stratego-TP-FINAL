#include "gameOverState.h"



gameOverState::gameOverState()
{
	state = GAME_OVER;
}

gameState * gameOverState::OnPlayAgain(GameModel * p2GameModel)
{

	return nullptr;
}

gameState * gameOverState::OnGameOver(GameModel * p2GameModel)
{
	return nullptr;
}


gameOverState::~gameOverState()
{
}
