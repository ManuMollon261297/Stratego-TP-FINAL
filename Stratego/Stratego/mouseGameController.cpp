#include "mouseGameController.h"
#include "gameState.h"
#include "IdleState.h"
#include "MyMoving.h"
#include "OpMoving.h"
#include "MyTurn.h"
#include "OpTurn.h"
#include "PlacingFichas.h"
#include "finishingPlacing.h"
#include "MyAttacking.h"
#include "OpAttacking.h"
#include "gameOverState.h"
#include "PlaAgainSelected.h"
#include "gameOverSelected.h"
#include "plaAgainSelected.h"


mouseGameController::mouseGameController(int h, int w, GameModel * p2gameModel_)
{

	p2gameModel = p2gameModel_;
	estadoModel_ = new PlacingFichas;
	Mstate = NONE_SELECTED;

	screenHeight = (unsigned int) h;
	screenWidth = (unsigned int) w;
	fichaHeight = (unsigned int)(h / 11);
	fichaWidth = (unsigned int) (w / 12)+5; //5 de recuadro de imagen
	cemeteryMargenY = fichaHeight; //margen superior
	cemeteryMargenX = 0;
	cemeteryHeight = screenHeight - cemeteryMargenY;  //cemetery dispuesto verticalmente
	cemeteryWidth = fichaWidth - cemeteryMargenX;
	battlefieldMargenY = cemeteryMargenY;
	battlefieldMargenX = cemeteryMargenX + cemeteryWidth+ 20; //20 de recuadro vertical
	battlefieldHeight = screenHeight - battlefieldMargenY; 
	battlefieldWidth = screenWidth - battlefieldMargenX-20; //20 de recuadro vertical

	initButtons();
	
}

GameModel * mouseGameController::getP2model()
{
	return p2gameModel;
}

void * mouseGameController::getp2estadoModel()
{
	return estadoModel_;
}

void mouseGameController::saveEvent(MouseInfo & Mev)
{
	memoryEv = Mev;
}

MouseInfo & mouseGameController::getPreviousEvent()
{
	return memoryEv;
}

bool mouseGameController::isEqualToPrevious(MouseInfo & Mev)
{
	bool ret;
	if ((memoryEv.r == Mev.r) && (memoryEv.evPos == Mev.evPos))
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}



MouseInfo mouseGameController::shape(double x, double y)
{
	cout << "x: " << x << "y: "<< y <<endl;
	MouseInfo Mev;
	Mev.sector = getSectorTouched(x, y);
	switch (Mev.sector)
	{
		case FRIENDLY_BATTLEFIELD:
		case HOSTIL_BATTLEFIELD:
		case NEUTRAL_BATTLEFIELD:
			Mev.evPos = translateBattlefieldCoords(x, y);
			Mev.type = fetchMevType(Mev.evPos);
			Mev.r = fetchMevRank(Mev.evPos);
			break;
		case CEMETERY_SECTOR:
			Mev.evPos = translateCemeteryCoords(x, y);
			Mev.r = fetchMevRankFromCemetery(Mev.evPos.y);
			Mev.type = CEMETERY_EV;
			break;
		case BOMB_SECTOR:
			Mev.r = BOMB;
			Mev.type = CEMETERY_EV;
			break;
		case FLAG_SECTOR:
			Mev.r = FLAG;
			Mev.type = CEMETERY_EV;
			break;
		case BOTON_PLACE_READY:
			Mev.type = BOTON_PLACE_READY_EV;
			break;
		case BOTON_SOUND:
			Mev.type = BOTON_SOUND_EV;
			break;
		case BOTON_GAME_OVER:
			Mev.type = GAME_OVER_EV;
			break;
		case BOTON_PLAY_AGAIN:
			Mev.type = PLAY_AGAIN_EV;
			break;
		case INVALID_SECTOR:
			Mev.evPos = { -1, -1 };
			Mev.type = NO_EVENT;
			break;
	}

	return Mev;
}

void mouseGameController::dispatch(GenericEvent& Mev)
{
	if(Mev.GetEvent() == MOUSE)
	{
		
		MouseEvent& ev = (MouseEvent&)Mev;
		MouseInfo info = shape(ev.x, ev.y);

		updateControllerState(p2gameModel->getState());
		gameState * proximoEstado = nullptr;  //puntero que funciona como memoria para el proximo estado
		gameState * estadoModel = (gameState *)estadoModel_;  //se crea un puntero auxiliar para poder desreferenciar
		switch (info.type)
		{
		case NO_EVENT:
			break;
		case SOLDIER_EV:
			proximoEstado = estadoModel->OnSoldier(info, Mstate, this, p2gameModel);
			break;
		case OPONENT_EV:
			proximoEstado = estadoModel->OnOponent(info, Mstate, this, p2gameModel);
			break;
		case LAND_EV:
			proximoEstado = estadoModel->OnLand(info, Mstate, this, p2gameModel);
			break;
		case WATER_EV:
			proximoEstado = estadoModel->OnWater(info, Mstate, this, p2gameModel);
			break;
		case CEMETERY_EV:
			proximoEstado = estadoModel->OnCemetery(info, Mstate, this, p2gameModel);
			break;
		case BOTON_PLACE_READY_EV:
			proximoEstado = estadoModel->OnConfirmPlaces(p2gameModel, Mstate);
			break;
		case BOTON_SOUND_EV:
			proximoEstado = estadoModel->OnSound(p2gameModel);
			break;
		case GAME_OVER_EV:
			proximoEstado = estadoModel->OnGameOver(p2gameModel);
			break;
		case PLAY_AGAIN_EV:
			proximoEstado = estadoModel->OnPlayAgain(p2gameModel);
			break;
		}

		if (proximoEstado != nullptr) //hubo cambio de estado
		{
			delete estadoModel_;
			estadoModel_ = (void *) new gameState;
			estadoModel_ = proximoEstado;
			proximoEstado = nullptr;
			updateModelState();
		}
	}
	
}

sectors mouseGameController::getSectorTouched(double x, double y)
{
	//sectors sectorRet;
	sectors sectorRet = INVALID_SECTOR;
	if ((p2gameModel->getState()) != GAME_OVER)
	{
		if (isCemeteryTouched(x, y))
		{
			sectorRet = CEMETERY_SECTOR;
		}
		else if (isBombTouched(x, y))
		{
			sectorRet = BOMB_SECTOR;
		}
		else if (isFlagTouched(x, y))
		{
			sectorRet = FLAG_SECTOR;
		}
		else if (isBattlefieldTouched(x, y))
		{
			if (isFriendlyBattlefieldTouched(x, y))
			{
				sectorRet = FRIENDLY_BATTLEFIELD;
			}
			else if (isHostilBattlefieldTouched(x, y))
			{
				sectorRet = HOSTIL_BATTLEFIELD;
			}
			else
			{
				sectorRet = NEUTRAL_BATTLEFIELD;
			}
		}
		else
		{
			sectorRet = INVALID_SECTOR;
		}
		if ((p2gameModel->getState()) == PLACING_FICHAS) //me fijo si se toco algun boton
		{
			if (p2gameModel->getButtonReference(PLACE_READY_B) != nullptr) //me fijo si existe el boton de finish placing fichas
			{
				if (p2gameModel->getButtonReference(PLACE_READY_B)->isTouched(x, y)) //me fijo si se selecciono
				{
					sectorRet = BOTON_PLACE_READY;
				}
			}
		}
		if (p2gameModel->getButtonReference(SOUND_B) != nullptr) //me fijo si existe el boton de finish placing fichas
		{
			if (p2gameModel->getButtonReference(SOUND_B)->isTouched(x, y)) //me fijo si se selecciono
			{
				sectorRet = BOTON_SOUND;
			}
		}
	}
	
	else if ((p2gameModel->getState()) == GAME_OVER)
	{
		if (p2gameModel->getButtonReference(PLAY_AGAIN_B) != nullptr)
		{
			if (p2gameModel->getButtonReference(PLAY_AGAIN_B)->isTouched(x, y))
			{
				sectorRet = BOTON_PLAY_AGAIN;
			}
		}
		if (p2gameModel->getButtonReference(GAME_OVER_B) != nullptr)
		{
			if (p2gameModel->getButtonReference(GAME_OVER_B)->isTouched(x, y))
			{
				sectorRet = BOTON_GAME_OVER;
			}
		}
		else
		{
			sectorRet = INVALID_SECTOR;
		}
	}

	return sectorRet;
}

pos mouseGameController::translateBattlefieldCoords(double x, double y)
{
	pos ret;

	ret.y = (int) ((x - battlefieldMargenX) / fichaWidth);  //devuelve coordenada entera entre 0 y la cantidad de columnas -1
	ret.x = (int) ((y - battlefieldMargenY) / fichaHeight);  //devuelve coordenada entera entre 0 y la cantidad de filas -1

	return ret;
}

pos mouseGameController::translateCemeteryCoords(double x, double y)
{
	pos ret;

	ret.x = -1; //pos.x siempre se setea en -1
	ret.y = (int)((y - cemeteryMargenY) / fichaHeight);

	return ret;
}

notstd::rank mouseGameController::fetchMevRank(pos p)
{
	return (p2gameModel->getRankFromPos(p));
}

notstd::rank mouseGameController::fetchMevRankFromCemetery(int y)
{
	notstd::rank r;
	switch (y)
	{
	case 0: r = MARSHAL; break;
	case 1: r = GENERAL; break;
	case 2: r = CORONEL; break;
	case 3: r = MAJOR; break;
	case 4: r = CAPTAIN; break;
	case 5: r = LIEUTENANT; break;
	case 6: r = SERGEANT; break;
	case 7: r = MINER; break;
	case 8: r = SCOUT; break;
	case 9: r = SPY; break;
	case 10: r = BOMB; break;
	case 11: r = FLAG; break;
	case 12: r = WATER; break;
	case 13: r = OTHERS; break;
	case 14: r = LAND; break;
	}
	return r;
}

Mevents mouseGameController::fetchMevType(pos pos_)
{
	Mevents ret;
	notstd::rank rank_ = p2gameModel->getRankFromPos(pos_);
	if (rank_ == LAND)
	{
		ret = LAND_EV;
	}
	else if (rank_ == WATER)
	{
		ret = WATER_EV;
	}
	else if (rank_ == OTHERS)
	{
		ret = OPONENT_EV;
	}
	else
	{
		ret = SOLDIER_EV;
	}

	return ret;
}

bool mouseGameController::fetchObstacle(int fijoOri, int movilOri, int fijoDest, int varDest, char c_recorrido)
{
	bool ret = true;
	int potentialObstacles = 0;
	pos recorrido;
	if (c_recorrido == 'y')
	{
		recorrido.x = fijoOri;
		recorrido.y = movilOri;
		if ((movilOri) > (varDest)) //se mueve para atras
		{
			potentialObstacles = movilOri - varDest - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.y = movilOri - i;  //recorre hacia atras
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
		else //se mueve para adelante
		{
			potentialObstacles = varDest - movilOri - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.y = (memoryEv.evPos.y) + i;  //recorre hacia adelante
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
	}
	else if (c_recorrido == 'x')
	{
		recorrido.y = fijoOri;
		recorrido.x = movilOri;
		if ((movilOri) > (varDest)) //se mueve para atras
		{
			potentialObstacles = movilOri - varDest - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.x = movilOri - i;  //recorre hacia atras
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
		else //se mueve para adelante
		{
			potentialObstacles = varDest - movilOri - 1;
			for (int i = 1; (i <= potentialObstacles) && (ret); i++)
			{
				recorrido.x = (memoryEv.evPos.y) + i;  //recorre hacia adelante
				if ((p2gameModel->getRankFromPos(recorrido)) != LAND)
				{
					ret = false;
				}
			}
		}
	}

	
	

	return !ret; //devuelve true si hubo obstaculo, false si  en el medio solo hay LAND
}

void mouseGameController::updateControllerState(int modelState)
{
	gameState * estadoModel = (gameState *)estadoModel_;  //se crea un puntero auxiliar para poder desreferenciar
	if ((estadoModel != nullptr) && (p2gameModel->getState() != estadoModel->getState()))
	{
		delete estadoModel_;
		switch (p2gameModel->getState())
		{
			case MY_TURN:
				estadoModel_ = new MyTurn;
				break;
			case OP_TURN:
				estadoModel_ = new OpTurn;
				break;
			case MY_ATTACKING:
				estadoModel_ = new MyAttacking;
				break;
			case OP_ATTACKING:
				estadoModel_ = new OpAttacking;
				break;
			case MY_MOVING:
				estadoModel_ = new MyMoving;
				break;
			case OP_MOVING:
				estadoModel_ = new OpMoving;
				break;
			case PLACING_FICHAS:
				estadoModel_ = new PlacingFichas;
				break;
			case IDLE:
				estadoModel_ = new IdleState;
				break;
			case GAME_OVER:
				estadoModel_ = new gameOverState;
				break;
			case ENDING_PLACING_FICHAS:
				estadoModel_ = new finishingPlacing;
				break;
			case PLAY_AGAIN_SELECTED:
				estadoModel_ = new plaAgainSelected;
				break;
			case GAME_OVER_SELECTED:
				estadoModel_ = new gameOverSelected;
				break;
			default:  //esto no hace falta, pero esta por si en algun momento el switch no llegara a contemplar todos los casos
				estadoModel_ = new IdleState;
				break;
		}
	}
}

void mouseGameController::updateModelState()
{
	int m_state = ((gameState *)estadoModel_)->getState();
	if ((p2gameModel->getState()) != m_state)
	{
		p2gameModel->setState(m_state);
	}
	
}

bool mouseGameController::isCemeteryTouched(int x, int y)
{
	return  ( ( (x > cemeteryMargenX) && (x < (cemeteryMargenX + cemeteryWidth)) ) && ( (y > cemeteryMargenY) && (y < (cemeteryMargenY + cemeteryHeight)) ) )  ;

}

bool mouseGameController::isBombTouched(int x, int y)
{
	return ( ( (x > cemeteryMargenX) && (x < (cemeteryMargenX + (cemeteryWidth*1))) && (y > 0) && (y < (cemeteryMargenY))) );
}

bool mouseGameController::isFlagTouched(int x, int y)
{
	return (((x > (cemeteryMargenX + (cemeteryWidth * 1))) && (x < (cemeteryMargenX + (cemeteryWidth * 2))) && (y > 0) && (y < (cemeteryMargenY))));
}

bool mouseGameController::isBattlefieldTouched(int x, int y)
{
	return (((x > battlefieldMargenX) && (x < (battlefieldMargenX + battlefieldWidth))) && ((y > battlefieldMargenY) && (y < (battlefieldMargenY + battlefieldHeight))));
}

bool mouseGameController::isFriendlyBattlefieldTouched(int x, int y)
{
	return  (((x > battlefieldMargenX) && (x < (battlefieldMargenX + battlefieldWidth))) && ((y > battlefieldMargenY + battlefieldHeight - (4 * fichaHeight)) && (y < (battlefieldMargenY + battlefieldHeight))));
}

bool mouseGameController::isHostilBattlefieldTouched(int x, int y)
{
	return (((x > battlefieldMargenX) && (x < (battlefieldMargenX + battlefieldWidth))) && ((y > battlefieldMargenY) && (y < (battlefieldMargenY + (4 * fichaHeight)))));
}

void mouseGameController::initButtons(void)
{
	gameDataButtonsPos buttonsInfo;
	buttonsInfo.ll_done.x = 963;
	buttonsInfo.ll_done.y = 64;
	buttonsInfo.ll_playAgain.x = 380;
	buttonsInfo.ll_playAgain.y = 625;
	buttonsInfo.ll_sound.x = 885;
	buttonsInfo.ll_sound.y = 64;
	buttonsInfo.ll_exit.x = 377;
	buttonsInfo.ll_exit.y = 515;
	buttonsInfo.hr_done.x = 1066;
	buttonsInfo.hr_done.y = 5;
	buttonsInfo.hr_playAgain.x = 704;
	buttonsInfo.hr_playAgain.y = 538;
	buttonsInfo.hr_sound.x = 950;
	buttonsInfo.hr_sound.y = 5;
	buttonsInfo.hr_exit.x = 704;
	buttonsInfo.hr_exit.y = 427;

	button playAgain_b(PLAY_AGAIN_B, buttonsInfo.ll_playAgain, buttonsInfo.hr_playAgain);
	button exit_b(GAME_OVER_B, buttonsInfo.ll_exit, buttonsInfo.hr_exit);
	button sound_b(SOUND_B, buttonsInfo.ll_sound, buttonsInfo.hr_sound);
	button done_b(PLACE_READY_B, buttonsInfo.ll_done, buttonsInfo.hr_done);

	p2gameModel->pushButton(playAgain_b);
	p2gameModel->pushButton(exit_b);
	p2gameModel->pushButton(sound_b);
	p2gameModel->pushButton(done_b);

}

bool mouseGameController::validOffsetMovement(pos destiny)
{
	bool ret= false;
	int offset = 0;
	if (((memoryEv.evPos.x) == (destiny.x)) || ((memoryEv.evPos.y) == (destiny.y)))
	{
		if ((memoryEv.evPos.x) == (destiny.x))
		{
			offset = ((memoryEv.evPos.y > destiny.y) ? (memoryEv.evPos.y - destiny.y) : (destiny.y - memoryEv.evPos.y));
			if (offset <= p2gameModel->getMaxOffsetFromPos(memoryEv.evPos))
			{
				ret = true;
			}
		}
		else
		{
			offset = ((memoryEv.evPos.x > destiny.x) ? (memoryEv.evPos.x - destiny.x) : (destiny.x - memoryEv.evPos.x));
			if (offset <= p2gameModel->getMaxOffsetFromPos(memoryEv.evPos))
			{
				ret = true;
			}
		}
	}
	
	return ret;
}

bool mouseGameController::validObstacles(pos destiny)  //debe llamarse luego de validOffset, sino no sirve
{
	bool ret = false;
	if ((memoryEv.evPos.x) == (destiny.x)) //se mueve en 'y', en 'x' queda fijo
	{
		ret = !fetchObstacle(memoryEv.evPos.x, memoryEv.evPos.y, destiny.x, destiny.y, 'y');
	}
	else //se mueve en 'x', en 'y' queda fijo.
	{
		ret = !fetchObstacle(memoryEv.evPos.y, memoryEv.evPos.x, destiny.y, destiny.x, 'x');
	}
	

	return ret;
}


mouseGameController::~mouseGameController()
{
	delete estadoModel_;
}
