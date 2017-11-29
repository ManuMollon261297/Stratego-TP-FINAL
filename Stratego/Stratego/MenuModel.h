#pragma once
#include <string>
#include <vector>
#include "button.h"

class MenuModel
{
public:
	MenuModel();
	~MenuModel(); //manejo de archivos
	int getState();
	void setState(int state_);
	bool getWorkingIp();
	void setWorkingIp(bool isIp);
	void addCharToWorkingString(char a);
	void deleteCharToWorkingString();
	void pushButton(button b);
	void deleteButtons();
private:
	std::string bakcUpFile;
	std::string leaderboardFile;
	int state;
	bool workingIp;
	std::string name;
	std::string ip;
	std::vector<button> botones;
};

