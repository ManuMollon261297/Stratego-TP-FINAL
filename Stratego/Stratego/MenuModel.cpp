#include "MenuModel.h"



MenuModel::MenuModel()
{
}


MenuModel::~MenuModel()
{
}

int MenuModel::getState()
{
	return state;
}

void MenuModel::setState(int state_)
{
	state = state_;
}

bool MenuModel::getWorkingIp()
{
	return workingIp;
}

void MenuModel::setWorkingIp(bool isIp)
{
	workingIp = isIp;
}

void MenuModel::addCharToWorkingString(char a)
{
}

void MenuModel::deleteCharToWorkingString()
{
}

void MenuModel::pushButton(button b)
{
}

void MenuModel::deleteButtons()
{
}
