#include "GameModel.h"
#include "MenuModel.h"
#include <iostream>

int main()
{
	MenuModel * menu = new MenuModel;
	std::vector<char> info;
	pos pos1(0,0);
	pos pos2(100,100);
	button boton(0,pos1 ,pos2);
	menu->addCharToWorkingString('M');
	menu->addCharToWorkingString('a');
	menu->addCharToWorkingString('n');
	menu->addCharToWorkingString('u');
	menu->setWorkingIp(true);
	menu->addCharToWorkingString('1');
	menu->addCharToWorkingString('2');
	menu->addCharToWorkingString('3');
	menu->addCharToWorkingString('4');
	menu->pushButton(boton);
	button * auxBoton = menu->getButtonReference(0);
	auxBoton->getIndex();
	auxBoton->press();
	std::cout<< auxBoton->getPressStatus() << std::endl;
	menu->deleteButtons();
	info = menu->getLeadreboardInfo();
	delete menu;
	getchar();
	return 0;
}

