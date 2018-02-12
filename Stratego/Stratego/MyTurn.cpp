#include "MyTurn.h"
#include "MyAttacking.h"
#include "MyMoving.h"



MyTurn::MyTurn()
{
	state = MY_TURN;
}

gameState * MyTurn::OnSoldier(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
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
		p2controller->saveEvent(Mev);
		break;
	}
	return nullptr;
}

gameState * MyTurn::OnCemetery(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("This soldiers had been defeated");
	return nullptr;
}

gameState * MyTurn::OnOponent(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	gameState * pRet = nullptr;
	switch (Mstate)
	{
	case NONE_SELECTED:
		p2GameModel->setMessage("Hostiles troops");
		break;
	case SOLDIER_SELECTED:
		if (p2controller->validOffsetMovement(Mev.evPos))
		{
			if (p2controller->validObstacles(Mev.evPos))
			{
				p2GameModel->move(p2controller->getPreviousEvent().evPos, Mev.evPos); //aca podria llegarse a cambiar el gameState a MY_MOVING
				Mstate = NONE_SELECTED;
				p2GameModel->setMoveDoneTrue();
				pRet = new MyAttacking;
			}
			else
			{
				p2GameModel->setMessage("You can't make that movement");
				//no se cambia estado, ni de mouse, ni de game.
			}
		}
		else
		{
			p2GameModel->setMessage("This troop can't walk that distance");
			//no se cambia estado, ni de mouse, ni de game.
		}

		break;
	}
	return pRet;
}

gameState * MyTurn::OnLand(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	gameState * pRet = nullptr;
	switch (Mstate)
	{
	case NONE_SELECTED:
		p2GameModel->setMessage("Empty place");
		break;
	case SOLDIER_SELECTED:
		if (p2controller->validOffsetMovement(Mev.evPos))
		{
			if (p2controller->validObstacles(Mev.evPos))
			{
				p2GameModel->unselectFicha(p2controller->getPreviousEvent().evPos);
				p2GameModel->move(p2controller->getPreviousEvent().evPos, Mev.evPos); //aca podria llegarse a cambiar el gameState a MY_MOVING
				Mstate = NONE_SELECTED;
				pRet = new MyMoving;
			}
			else
			{
				p2GameModel->setMessage("Can not do that, obstalces...");
				//no se cambia estado, ni de mouse, ni de game.
			}
		}
		else
		{
			p2GameModel->setMessage("This troop can't walk that distance");
			//no se cambia estado, ni de mouse, ni de game.
		}
		
		break;
	}
	return pRet;
}

gameState * MyTurn::OnWater(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("The troops can't walk through the lake");
	return nullptr;
}


MyTurn::~MyTurn()
{
}
