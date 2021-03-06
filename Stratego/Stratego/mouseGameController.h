#pragma once
#include "GenericController.h"
#include "GameModel.h"
#include "MouseEvent.h"
enum MouseStates { NONE_SELECTED, SOLDIER_SELECTED, CEMETERY_SELECTED };


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
#define MARGEN_X_BATTLEFIELD MARGEN_X_CEMETERY + SIZE_CEMETERY_X //cemetery a la izquierda de battlefield
#define MARGEN_Y_BATTLEFIELD SIZE_CASILLERO_Y


class mouseGameController : public GenericController
{
public:
	mouseGameController(int h, int w, GameModel * p2gameModel_);
	GameModel * getP2model();
	void * getp2estadoModel();
	

	void saveEvent(MouseInfo & Mev);
	MouseInfo & getPreviousEvent();
	bool isEqualToPrevious(MouseInfo & Mev);

	bool validOffsetMovement(pos destiny); //se fija si el offset de la ficha permite llegar hasta ese punto, la posicion original de la ficha
										   //se encuentra en memoryEv.
										   //return:  valido --> true; invalido --> false.
	bool validObstacles(pos destiny); //debe llamarse luego de validOffsetMovement, sino no sirve esta funcion.
									  //se fija si no hay obstaculos que impidan el movimiento
									  //return:  valido --> true (NO hay obstaculos); invalido --> false(HAY obstaculos).

	MouseInfo shape(double x, double y); //devuelve un evento de mouse sheipeado

	virtual void dispatch(GenericEvent& Mev);

	~mouseGameController();
private:

	unsigned int screenWidth;
	unsigned int screenHeight;
	unsigned int fichaHeight;
	unsigned int fichaWidth;
	unsigned int cemeteryHeight;
	unsigned int cemeteryWidth;
	unsigned int cemeteryMargenX;
	unsigned int cemeteryMargenY;
	unsigned int battlefieldHeight;
	unsigned int battlefieldWidth;
	unsigned int battlefieldMargenX;
	unsigned int battlefieldMargenY;

	GameModel * p2gameModel;

	void * estadoModel_;

	MouseStates Mstate;


	MouseInfo memoryEv;
	

	sectors getSectorTouched(double x, double y);

	pos translateBattlefieldCoords(double x, double y);
	pos translateCemeteryCoords(double x, double y); //en pos.y se devuelve el indice correspondiente del arreglo de cemetery. 
															//En pos.x siempre se devuelve -1

	notstd::rank fetchMevRank(pos p);
	notstd::rank fetchMevRankFromCemetery(int y);
	
	Mevents fetchMevType(pos pos_);

	bool fetchObstacle(int fijoOri, int movilOri, int fijoDest, int varDest, char c_recorrido); //funcion utilizada por validObstacles()

	void updateControllerState(int modelState); //coordina los estados del model entre las clases model y controller, antes de entrar a la fsm de controller
	void updateModelState(); //coordina los estados del model entre las clases model y controller, luego de pasar fsm de controller

	bool isCemeteryTouched(int x, int y);
	bool isBombTouched(int x, int y);
	bool isFlagTouched(int x, int y);
	bool isBattlefieldTouched(int x, int y);
	bool isFriendlyBattlefieldTouched(int x, int y);
	bool isHostilBattlefieldTouched(int x, int y);

	void initButtons(void);
};