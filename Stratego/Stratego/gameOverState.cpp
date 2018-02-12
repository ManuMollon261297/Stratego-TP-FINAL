#include "gameOverState.h"



gameOverState::gameOverState()
{
	state = GAME_OVER;
}

gameState * gameOverState::OnPlayAgain(GameModel * p2GameModel)
{
	gameState * proxEstado = new plaAgainSelected;
	return proxEstado;
}

gameState * gameOverState::OnGameOver(GameModel * p2GameModel)
{
	gameState * proxEstado = new gameOverSelected;
	return nullptr;
}


gameOverState::~gameOverState()
{
}
