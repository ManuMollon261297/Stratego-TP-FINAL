#include "MyTurn.h"



MyTurn::MyTurn()
{
	state = MY_TURN;
}

gameState * MyTurn::OnSoldier(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		Mstate = SOLDIER_SELECTED;
		p2GameModel->selectFicha(Mev.evPos);
		p2controller->saveEvent(Mev);
		break;
	case SOLDIER_SELECTED:
		p2GameModel->unselectFicha(p2controller->getPreviousEvent().evPos);
		if (!(p2controller->isEqualToPrevious(Mev)))
		{
			p2GameModel->selectFicha(Mev.evPos);
		}
		else
		{
			Mstate = NONE_SELECTED;
		}
		break;
	}
	return nullptr;
}

gameState * MyTurn::OnCemetery(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("Estos soldados han sido derrotados, estan fuera de combate");
	return nullptr;
}

gameState * MyTurn::OnOponent(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		p2GameModel->setMessage("Tropas hostiles");
		break;
	case SOLDIER_SELECTED:
		if (p2controller->validOffsetMovement(Mev.evPos))
		{
			if (p2controller->validObstacles(Mev.evPos))
			{
				p2GameModel->move(p2controller->getPreviousEvent().evPos, Mev.evPos); //aca podria llegarse a cambiar el gameState a MY_MOVING
				p2GameModel->setMessage("Movimiento ofensivo");
				Mstate = NONE_SELECTED;
			}
			else
			{
				p2GameModel->setMessage("No se puede realizar el movimiento, hay obstaculos en el medio");
				//no se cambia estado, ni de mouse, ni de game.
			}
		}
		else
		{
			p2GameModel->setMessage("La tropa no esta habilitada a recorrer la distancia indicada");
			//no se cambia estado, ni de mouse, ni de game.
		}

		break;
	}
	return nullptr;
}

gameState * MyTurn::OnLand(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		p2GameModel->setMessage("Terreno vacio");
		break;
	case SOLDIER_SELECTED:
		if (p2controller->validOffsetMovement(Mev.evPos))
		{
			if (p2controller->validObstacles(Mev.evPos))
			{
				p2GameModel->move(p2controller->getPreviousEvent().evPos, Mev.evPos); //aca podria llegarse a cambiar el gameState a MY_MOVING
				p2GameModel->setMessage("Movimiento inofensivo"); 
				Mstate = NONE_SELECTED;
			}
			else
			{
				p2GameModel->setMessage("No se puede realizar el movimiento, hay obstaculos en el medio");
				//no se cambia estado, ni de mouse, ni de game.
			}
		}
		else
		{
			p2GameModel->setMessage("La tropa no esta habilitada a recorrer la distancia indicada");
			//no se cambia estado, ni de mouse, ni de game.
		}
		
		break;
	}
	return nullptr;
}

gameState * MyTurn::OnWater(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("Lago, por aqui las tropas no pueden pasar");
	return nullptr;
}


MyTurn::~MyTurn()
{
}
