#pragma once

#include "ranks.h"
#include "ficha.h"
#include "currStatus.h"
#include "pos.h"
#include "button.h"
#include "GenericModel.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define LEADERBOARDDIR "STPFLB.txt"

#define FILAS			10
#define COLUMNAS		10
#define TIPOS_DE_RANK	12
#define MAX_CANT_MOVEMENTS_REPETEAD 3


enum states {
	MY_TURN, OP_TURN, MY_ATTACKING, OP_ATTACKING, MY_MOVING, OP_MOVING, PLACING_FICHAS, GAME_OVER, IDLE
	, ENDING_PLACING_FICHAS, WAITING_FOR_OPPONENTS_SELECTION, PLAY_AGAIN_SELECTED, GAME_OVER_SELECTED
};

class GameModel : public GenericModel
{
public:
	GameModel();
	//state
	int getState();
	void setState(int state_);

	//Opponent
	void SetOpponentName(std::string);
	std::string& GetOpponentName();

	//Exit
	void SetExit(bool);

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

	void resolveAttack(notstd::rank r); //resuelve un ataque pendiente con la info en currStatus

	notstd::rank getRankFromPos(pos currpos);
	unsigned int getNumberInCemetery(notstd::rank r);
	int getMaxOffsetFromPos(pos currpos);
	bool isSelectedFromPos(pos currpos);
	bool isCemeteryEmpty();
	bool isRankCemeterySelected(notstd::rank r);
	bool isAttackResolved()const; 
	//ficha
	void swap(pos init, pos final); //asume cambio de coordenadas validas, previamente chequeadas
	bool setFicha(notstd::rank r, pos x);	//setea si es valida, una ficha en el tablero, devuelve false si no fue posible
									//usa cemetery para validar el uso de esa ficha y el battlefield para validar las coord
	void selectFicha(pos p);
	void unselectFicha(pos p);
	void toggleFicha(pos p);
	void selectRankCemetery(notstd::rank r);
	void unselectRankCemetery(notstd::rank r);
	void unselectAllExcepetOneRankCemetery(notstd::rank r);
	void unselectAllCemetery(void);
	void unselectAllBattlefield(void);
	void toggleSelectRankCemetery(notstd::rank r);

	bool checkMoveRepetead(pos prev, pos next);

	void randomPos();

	void setFichasPlacedTrue();
	void setFichasPlacedFalse();
	bool getFichasPlaced();
	void reset();
	//manejo de botones

	button * getButtonReference(int index);
	void pushButton(button b);
	void deleteButtons();

	void toggleMute(void);

	//timer
	void decrementTime();
	void restartTimer();

	bool getMoveDone();
	void setMoveDoneTrue();
	void setMoveDoneFalse();
	void setMute(bool state);
	void setAttackResolvedFalse(void);
	//Getters
	int getTime()const;
	currStatus GetmyPosStatus()const;
	currStatus GetopPosStatus()const;
	bool GetExit()const;
	bool isMuteOn()const;
	notstd::rank getOpponentRank()const;
	notstd::rank getMyRank()const;

	//winner
	void playerWon();
	bool didPlayerWin();
	bool updateLeaderboard(std::string& winner);
	
	//verify
	bool verifyMovement(); //chequea si el jugador puede hacer una movida, si no puede, el jugador pierde
	bool verifyRescue(); //verifica si en la posicion actual el jugador es apto para hacer un rescue
	//destructor
	virtual ~GameModel();
	//debug
	void printBattlefield();
private:
	notstd::rank opRank;
	notstd::rank myRank;
	bool gameOver;
	bool Exit; //Se pone en true cuando sucede alguna situacion que genera el cierre del programa.
	bool mute;
	bool red;
	ficha * battlefield[FILAS][COLUMNAS]; //la parte alta es la del contrario y la baja la del final
	//std::vector<ficha> queue;
	int cemetery[TIPOS_DE_RANK+1][3];	// matriz que contiene los rangos, la cantidad de estos que se encuentran
										// fuera de juego, y si estos rangos estan seleccionados (1) o no lo estan (0).
	int state; //estado actual del juego
	int timeRemaining;

	bool moveDone;
	bool fichasPlaced;
	bool won; //true si el jugador gano la partida
	bool attackResolved;

	currStatus myPosStatus;
	currStatus opPosStatus;
	int rescuesRemaining;
	int repeatMoveCounter;

	std::vector<button> botones;

	std::string message;
	std::string opponents_name;

	
	bool clearSurroundings(int i, int j);
	std::string intToString(unsigned int number);

};