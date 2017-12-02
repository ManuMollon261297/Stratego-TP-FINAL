#pragma once

#include "ficha.h"
#include "currStatus.h"
#include "pos.h"
#include "ranks.h"
#include "gameState.h"
#include <vector>
#include <iostream>

#define FILAS		10
#define COLUMNAS	10
#define TIPOS_DE_RANK	12



class GameModel
{
public:
	GameModel();
	//state
	int getState();
	void setState(int state_);

	//red
	bool getRed();
	void setRed(bool color);

	//message
	std::string & getMessage();
	void setMessage(char * message_);

	//game
	bool move(pos currPos, pos newPos);	//valida que los moves sean a un espacio vacio y los realiza
										//si corresponde a un ataque cambia el estado pero no realiza movimiento
										//si el movimineto no es valido devuelve false

	void resolveAttack(rank r); //resuelve un ataque pendiente con la info en currStatus

	rank getRankFromPos(pos currpos);
	unsigned int getNumberInCemetery(rank r);
	int getMaxOffsetFromPos(pos currpos);
	bool isSelectedFromPos(pos currpos);
	bool isCemeteryEmpty();
	bool isRankCemeterySelected(rank r);
	//ficha
	void swap(pos init, pos final); //asume cambio de coordenadas validas, previamente chequeadas
	bool setFicha(rank r, pos x);	//setea si es valida, una ficha en el tablero, devuelve false si no fue posible
									//usa cemetery para validar el uso de esa ficha y el battlefield para validar las coord
	void selectFicha(pos p);
	void unselectFicha(pos p);
	void toggleFicha(pos p);
	void selectRankCemetery(rank r);
	void unselectRankCemetery(rank r);
	void toggleSelectRankCemetery(rank r);


	//timer
	int getTime();
	void decrementTime();
	void restartTimer();

	bool getMoveDone();
	void setMoveDoneTrue();
	void setMoveDoneFalse();

	//Getters
	currStatus GetmyPosStatus()const;
	currStatus GetopPosStatus()const;

	//winner
	void playerWon();
	bool didPlayerWin();
	//verify
	bool verifyMovement(); //chequea si el jugador puede hacer una movida, si no puede, el jugador pierde
	bool verifyRescue(); //verifica si en la posicion actual el jugador es apto para hacer un rescue
	//destructor
	~GameModel();
	//debug
	void printBattlefield();
private:
	bool gameOver;

	bool red;
	ficha * battlefield[FILAS][COLUMNAS]; //la parte alta es la del contrario y la baja la del final
	//std::vector<ficha> queue;
	int cemetery[TIPOS_DE_RANK+1][3];	// matriz que contiene los rangos, la cantidad de estos que se encuentran
										// fuera de juego, y si estos rangos estan seleccionados (1) o no lo estan (0).
	int state; //estado actual del juego
	int timeRemaining;

	bool moveDone;
	bool won; //true si el jugador gano la partida

	currStatus myPosStatus;
	currStatus opPosStatus;
	int rescuesRemaining;
	int repeatMoveCounter;

	std::string message;

	bool checkMoveRepetead(pos prev, pos next);
	bool clearSurroundings(int i, int j);

};