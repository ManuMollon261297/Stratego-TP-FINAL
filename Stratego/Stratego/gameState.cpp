#include "gameState.h"




gameState::gameState()
{

}


gameState::~gameState()
{
}

gameState * gameState::OnSoldier(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnCemetery(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnOponent(MouseInfo & ev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnLand(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnWater(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnConfirmPlaces(GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnPlayAgain(GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnGameOver(GameModel * p2GameModel)
{
	return nullptr;
}

int gameState::getState()
{
	return state;
}
