#pragma once
#include <string>
#include <vector>
#include "button.h"

class MenuModel
{
public:
	MenuModel();
	~MenuModel();
	int getState();
	void setState(int state_);
	bool getWorkingIp();
	void setWorkingIp(bool isIp);
	void addCharToWorkingString(char a);
	void deleteCharToWorkingString();
	void pushButton(button b);
	void deleteButtons();
	button * getButtonReference(int index);
	std::vector<char> getLeadreboardInfo();
private:
	std::string bakcUpFile;
	std::string leaderboardFile;
	int state;
	bool workingIp;
	std::string name;
	std::string ip;
	std::vector<button> botones;
};

