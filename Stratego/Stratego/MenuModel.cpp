#include "MenuModel.h"
#include <iostream>
#include <fstream>


MenuModel::MenuModel()
{
	bakcUpFile = "temporal.txt";
	leaderboardFile = "STPFLB.txt"; //Stratego Tp Final Leader Board
	workingIp = false;

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
	switch (workingIp)
	{
	case true:
		ip.push_back(a);
		break;
	case false:
		name.push_back(a);
		break;
	}
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
}

void MenuModel::pushButton(button b)
{
	botones.push_back(b);
}

void MenuModel::deleteButtons()
{
	botones.clear();
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

std::vector<char> MenuModel::getLeadreboardInfo()
{
	std::vector<char> info;
	std::string aux;
	std::ifstream lbFile;
	lbFile.open(leaderboardFile, std::ios::binary);
	if (lbFile.is_open())
	{
		while (getline(lbFile, aux))
		{
			std::copy(aux.begin(), aux.end(), std::back_inserter(info)); 
			info.push_back('\n');//aux a vector
		}
		lbFile.close();
	}
	return info;
}
