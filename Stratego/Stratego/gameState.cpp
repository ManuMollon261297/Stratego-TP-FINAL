#include "gameState.h"



gameState::gameState()
{

}


gameState::~gameState()
{
}

gameState * gameState::OnSoldier(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnCemetery(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnOponent(MouseEvent & ev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnLand(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

gameState * gameState::OnWater(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	return nullptr;
}

int gameState::getState()
{
	return state;
}
