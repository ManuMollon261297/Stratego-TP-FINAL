#pragma once
#include "ranks.h"
#include "GameModel.h"
#include "pos.h"
#include <string>

bool ValidateRank(unsigned char rank);
//Funcion que recibe el rank enviado por el oponente y valida que sea una de las opciones validas
//Devuelve false si e rank es invalido y true en caso contrario.

notstd::rank GetRank(unsigned char);
//Funcion que recibe el rank en formato de paquete y lo devuelve en el formato
//que usamos para realizar las cuentas.
//Si el rank es invalido devuelve WATER.

bool ValidateMovement(GameModel * Gm, pos& ori, pos& des);
//Funcion que valida que el movimiento del oponente sea valido.
//Devuelve false si es invalida, y true si es valida.

unsigned char ConvertRankToPackageFormat(notstd::rank);
//Recibee un rank y lo devuelve en el formato correcto para mandar en un
//paquete de attack. Si recibe un rank invalido devuelve '0'

void InvertPositionToLayout(pos* p);
//Se llama cuando soy azul para invertir la posicion de la logica
//al del layout de rojo en las filas 7, 8, 9, 10 y azul en las filas
//1, 2, 3, 4.

void DoLeaderBoardRoutine(GameModel * Gm, const std::string& winner);
//Funcion que actualiza el archivo del leaderboard y cambia el mensaje del gameModel para
//que informe lo ocurrido.