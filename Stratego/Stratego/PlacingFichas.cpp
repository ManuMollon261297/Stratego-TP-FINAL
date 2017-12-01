#include "PlacingFichas.h"



PlacingFichas::PlacingFichas()
{
	state = PLACING_FICHAS;
}


PlacingFichas::~PlacingFichas()
{
}

gameState * PlacingFichas::OnSoldier(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
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
			p2GameModel->setMessage("Esta posicion ya se encuentra cubierta, posiciona tu tropa en otro lugar");
			break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnCemetery(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		Mstate = CEMETERY_SELECTED;
		p2GameModel->selectRankCemetery(Mev.r);
		p2controller->saveEvent(Mev);
		break;
	case SOLDIER_SELECTED:
		p2GameModel->setMessage("Posiciona a tus soldados dentro del campo de batalla, dejalos combatir");
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
			p2GameModel->selectRankCemetery(Mev.r);
		}
		break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnOponent(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("Las tropas aun no estan preparadas para el ataque");
	return nullptr;
}

gameState * PlacingFichas::OnLand(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		p2GameModel->setMessage("Terreno vacio");
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
			p2GameModel->unselectRankCemetery(p2controller->getPreviousEvent.r);
			Mstate = NONE_SELECTED; //en este caso, se cambia el estado
		}
		
		break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnWater(MouseEvent & Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	p2GameModel->setMessage("Laguna, las tropas no pueden dirigirse alli");
	return nullptr;
}


