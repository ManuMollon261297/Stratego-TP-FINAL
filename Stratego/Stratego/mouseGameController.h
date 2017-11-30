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
	pos getFirstSelection();
	pos getSecondSelection();
	void setFirstSelection(pos p);
	void setSecondSelection(pos p);
	bool areSelectionsEquals(); //compara firstSelection con secondSelection

	~mouseGameController();
private:
	GameModel * p2gameModel;

	gameState * estadoModel;

	MouseStates Mstate;

	pos firstSelection;
	pos secondSelection;

	MouseEvent shape(double x, double y); //devuelve un evento de mouse sheipeado

	void dispatch(MouseEvent Mev);

	sectors getSectorTouched(double x, double y);

	pos translateBattlefieldCoords(double x, double y);
	pos translateCemeteryCoords(double x, double y); //en pos.y se devuelve el indice correspondiente del arreglo de cemetery. 
															//En pos.x siempre se devuelve -1
	
	Mevents fetchMevType(pos pos_);

};

