#include "GameModel.h"
#include <iostream>

int main()
{
	pos newpos(9, 0);
	pos newpos2(9, 1);
	pos newpos3(8, 0);
	pos newpos4(8, 1);
	//pos newpos5(0, 2);
	//pos newpos6(8, 7);
	//pos newpos7(0, 7);
	GameModel * engine = new GameModel;
	engine->setFicha(rank::MARSHAL, newpos);
	std::cout << engine->verifyMovement() << std::endl;
	engine->setFicha(rank::BOMB, newpos2);
	engine->setFicha(rank::BOMB, newpos3);
	engine->setFicha(rank::BOMB, newpos4);
	std::cout << engine->verifyMovement() << std::endl;
	engine->setState(states::MY_TURN);
	engine->printBattlefield();
	getchar();
	return 0;
}

