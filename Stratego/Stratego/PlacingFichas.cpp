#include "PlacingFichas.h"
#include "finishingPlacing.h"



PlacingFichas::PlacingFichas()
{
	state = PLACING_FICHAS;
}


PlacingFichas::~PlacingFichas()
{
}

gameState * PlacingFichas::OnSoldier(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
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
			Mstate = NONE_SELECTED;
			if (!(p2controller->isEqualToPrevious(Mev)))
			{
				p2GameModel->swap(p2controller->getPreviousEvent().evPos, Mev.evPos);
			}
			break;
		case CEMETERY_SELECTED:
			p2GameModel->setMessage("Position ocuppied");
			break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnCemetery(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		Mstate = CEMETERY_SELECTED;
		p2GameModel->selectRankCemetery(Mev.r);
		p2GameModel->unselectAllExcepetOneRankCemetery(Mev.r);
		p2controller->saveEvent(Mev);
		break;
	case SOLDIER_SELECTED:
		p2GameModel->setMessage("Position outside battlefield");
		break;
	case CEMETERY_SELECTED:
		//p2controller->setSecondSelection(Mev->evPos);
		//rank r1 = p2controller->fetchMevRankFromCemetery((p2controller->getFirstSelection().y));
		p2GameModel->unselectRankCemetery(p2controller->getPreviousEvent().r);
		if (p2controller->isEqualToPrevious(Mev))
		{
			Mstate = NONE_SELECTED;
		}
		else
		{
			p2controller->saveEvent(Mev);
			p2GameModel->selectRankCemetery(Mev.r);
		}
		break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnOponent(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("Army not ready...");
	return nullptr;
}

gameState * PlacingFichas::OnLand(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	if (Mev.sector == FRIENDLY_BATTLEFIELD)
	{
		switch (Mstate)
		{
		case NONE_SELECTED:
			p2GameModel->setMessage("Empty land");
			break;
		case SOLDIER_SELECTED:
			p2GameModel->unselectFicha(p2controller->getPreviousEvent().evPos);
			p2GameModel->swap(p2controller->getPreviousEvent().evPos, Mev.evPos);
			Mstate = NONE_SELECTED;
			break;
		case CEMETERY_SELECTED:

			p2GameModel->setFicha(p2controller->getPreviousEvent().r, Mev.evPos);
			//no cambia de estado, ni deselecciona la ficha del cementerio, ya que da la opcion de seguir colocando la misma ficha
			if (p2GameModel->getNumberInCemetery(p2controller->getPreviousEvent().r) == 0)
			{
				p2GameModel->unselectRankCemetery(p2controller->getPreviousEvent().r);
				Mstate = NONE_SELECTED; //en este caso, se cambia el estado
			}
			if (p2GameModel->isCemeteryEmpty())
			{
				//aqui se podria setear un flag que habilite el boton para confirmar las posiciones
			}

			break;
		}
	}
	else
	{
		p2GameModel->setMessage("No-man land");
	}
	
	return nullptr;
}

gameState * PlacingFichas::OnWater(MouseInfo & Mev, MouseStates & Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("Troops can't walk through lake");
	return nullptr;
}

gameState * PlacingFichas::OnConfirmPlaces(GameModel * p2GameModel)
{
	if (p2GameModel->isCemeteryEmpty())
	{
		p2GameModel->setFichasPlacedTrue();  //esto hara que el model de networking cambie el estado
		p2GameModel->setMessage("Ready for battle, waiting opponent");
		if (p2GameModel->getButtonReference(ENDING_PLACING_FICHAS) != nullptr)
		{
			p2GameModel->getButtonReference(ENDING_PLACING_FICHAS)->press(); //seleccion del boton
		}
		gameState * prox_estado = new finishingPlacing;
		return prox_estado;
	}
	else
	{
		p2GameModel->setMessage("Army not ready yet");
		return nullptr;
	}
}


