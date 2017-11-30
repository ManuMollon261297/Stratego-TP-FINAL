#include "PlacingFichas.h"



PlacingFichas::PlacingFichas()
{
}


PlacingFichas::~PlacingFichas()
{
}

gameState * PlacingFichas::OnSoldier(MouseEvent * Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		Mstate = SOLDIER_SELECTED;
		p2GameModel->selectFicha(Mev->evPos);
		p2controller->setFirstSelection(Mev->evPos);
		break;
		case SOLDIER_SELECTED:
			p2controller->setSecondSelection(Mev->evPos);
			p2GameModel->unselectFicha(p2controller->getFirstSelection());
			Mstate = NONE_SELECTED;
			if (!(p2controller->areSelectionsEquals()))
			{
				p2GameModel->swap(p2controller->getFirstSelection(), p2controller->getSecondSelection());
			}
			break;
		case CEMETERY_SELECTED:
			//falta decidir este caso.
			break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnCemetery(MouseEvent * Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		Mstate = CEMETERY_SELECTED;
		//selecciona el rango del cementerio (la info esta en mev.pos.y)
		p2controller->setFirstSelection(Mev->evPos);
		break;
	case SOLDIER_SELECTED:
		//falta decidir este caso!!!!
		break;
	case CEMETERY_SELECTED:
		p2controller->setSecondSelection(Mev->evPos);
		//desseleccionar el cementerio (con la FisrtSelection)
		if (!(p2controller->areSelectionsEquals()))
		{
			//seleccionar el cementerio (con la SecondSelection)
		}
		else
		{
			Mstate = NONE_SELECTED;
		}
		break;
	}
	return nullptr;
}

gameState * PlacingFichas::OnOponent(MouseEvent * Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	//rellena el string del model, diciendole que el ejercito aun no esta disponible para atacar.
	return nullptr;
}

gameState * PlacingFichas::OnLand(MouseEvent * Mev, MouseStates Mstate, mouseGameController * p2controller, GameModel * p2GameModel)
{
	switch (Mstate)
	{
	case NONE_SELECTED:
		//relleno el string del model con: "terreno vacío"
		break;
	case SOLDIER_SELECTED:
		p2GameModel->unselectFicha(p2controller->getFirstSelection());
		p2GameModel->swap(p2controller->getFirstSelection(), Mev->evPos);
		Mstate = NONE_SELECTED;
		break;
	case CEMETERY_SELECTED:

		p2GameModel->setFicha(p2GameModel->getRankFromPos(p2controller->getFirstSelection()), Mev->evPos);
		//no cambia de estado, ni deselecciona la ficha del cementerio, ya que da la opcion de seguir colocando la misma ficha
		
		break;
	}
	return nullptr;
}


