#pragma once
#include "GameModel.h"
#include "MouseEvent.h"
//dimensiones
#define CANT_CASILLEROS_X 10
#define CANT_CASILLEROS_Y 10
#define SIZE_BATTLEFIELD_X 800
#define SIZE_BATTLEFIELD_Y 800
#define SIZE_CASILLERO_X SIZE_BATTLEFIELD_X / CANT_CASILLEROS_X
#define SIZE_CASILLERO_Y SIZE_BATTLEFIELD_Y / CANT_CASILLEROS_Y
#define SIZE_CEMETERY_X SIZE_CASILLERO_X
#define SIZE_CEMETERY_Y SIZE_BATTLEFIELD_Y
#define MARGEN_X_CEMETERY SIZE_CASILLERO_X
#define MARGEN_Y_CEMETERY SIZE_CASILLERO_Y
#define MARGEN_X_BATTLEFIELD MARGEN_X_CEMETERY + SIZE_CEMETERY_X + SIZE_CASILLERO_X //cemetery a la izquierda de battlefield
#define MARGEN_Y_BATTLEFIELD SIZE_CASILLERO_Y

class mouseGameController
{
public:
	mouseGameController();
	GameModel * getP2model();
	

	void saveEvent(MouseEvent & Mev);
	MouseEvent & getPreviousEvent();
	bool isEqualToPrevious(MouseEvent & Mev);

	bool validOffsetMovement(pos destiny); //se fija si el offset de la ficha permite llegar hasta ese punto, la posicion original de la ficha
										   //se encuentra en memoryEv.
										   //return:  valido --> true; invalido --> false.
	bool validObstacles(pos destiny); //debe llamarse luego de validOffsetMovement, sino no sirve esta funcion.
									  //se fija si no hay obstaculos que impidan el movimiento
									  //return:  valido --> true (NO hay obstaculos); invalido --> false(HAY obstaculos).
	

	~mouseGameController();
private:
	GameModel * p2gameModel;

	gameState * estadoModel;

	MouseStates Mstate;


	MouseEvent memoryEv;
	

	MouseEvent shape(double x, double y); //devuelve un evento de mouse sheipeado

	void dispatch(MouseEvent Mev);

	sectors getSectorTouched(double x, double y);

	pos translateBattlefieldCoords(double x, double y);
	pos translateCemeteryCoords(double x, double y); //en pos.y se devuelve el indice correspondiente del arreglo de cemetery. 
															//En pos.x siempre se devuelve -1

	rank fetchMevRank(pos p);
	rank fetchMevRankFromCemetery(int y);
	
	Mevents fetchMevType(pos pos_);

	bool fetchObstacle(int fijoOri, int movilOri, int fijoDest, int varDest, char c_recorrido); //funcion utilizada por validObstacles()

	void updateControllerState(int modelState); //coordina los estados del model entre las clases model y controller, antes de entrar a la fsm de controller
	void updateModelState(); //coordina los estados del model entre las clases model y controller, luego de pasar fsm de controller
};