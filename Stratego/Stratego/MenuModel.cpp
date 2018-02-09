#include "MenuModel.h"
#include <iostream>
#include <fstream>


MenuModel::MenuModel()
{
	bakcUpFile = "temporal.txt";
	leaderboardFile = "STPFLB.txt"; //Stratego Tp Final Leader Board
	workingIp = false;
	exit = false;
	muteOn = false;
}

MenuModel::~MenuModel()
{
	std::ofstream infoFile;
	infoFile.open(bakcUpFile, std::ios::binary);
	infoFile << name << ' ' <<ip;
	infoFile.close();
}

int MenuModel::getState()
{
	return state;
}

void MenuModel::setState(int state_)
{
	state = state_;
	NotifyAllObservers();
}

bool MenuModel::GetExit(void)const
{
	return exit;
}

bool MenuModel::getWorkingIp()
{
	return workingIp;
}

void MenuModel::setWorkingIp(bool isIp)
{
	workingIp = isIp;
	NotifyAllObservers();
}

void MenuModel::addCharToWorkingString(char a)
{
	switch (workingIp)
	{
	case true:
		ip.push_back(a);
		break;
	case false:
		name.push_back(a);
		break;
	}
	NotifyAllObservers();
}

void MenuModel::deleteCharToWorkingString()
{
	switch (workingIp)
	{
	case true:
		if (ip.size() != 0)
		{
			ip.pop_back();
		}
		break;
	case false:
		if (name.size() != 0)
		{
			name.pop_back();
		}
		break;
	}
	NotifyAllObservers();
}

void MenuModel::pushButton(button b)
{
	botones.push_back(b);
	NotifyAllObservers();
}

void MenuModel::deleteButtons()
{
	botones.clear();
	NotifyAllObservers();
}

void MenuModel::setExit(void)
{
	exit = true;
	NotifyAllObservers();
}

void MenuModel::toggleSound()
{
	muteOn = !muteOn;
	NotifyAllObservers();
}

bool MenuModel::isMuteOn()
{
	return muteOn;
}

button * MenuModel::getButtonReference(int index)
{
	for (int i = 0; i < botones.size(); i++)
	{
		if (index == botones[i].getIndex())
		{
			return &botones[i];
		}
	}
	return nullptr;
}

std::vector<std::string> MenuModel::getLeadreboardInfo()
{
	std::vector<std::string> info;
	std::string aux;
	std::ifstream lbFile;
	lbFile.open(leaderboardFile, std::ios::binary);
	if (lbFile.is_open())
	{
		while (getline(lbFile, aux))
		{
			info.push_back(aux);
		}
		lbFile.close();
	}
	return info;
}

unsigned int MenuModel::getNumberOfButtons(void)
{
	return botones.size();
}

std::vector<button>& MenuModel::getButtonsVector(void)
{
	return botones;
}

std::string & MenuModel::getName(void)
{
	return name;
}

std::string MenuModel::getMessage(void)
{
	return message;
}

void MenuModel::setMessage(std::string message_)
{
	message = message_;
}
