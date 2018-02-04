#pragma once
#include <string>
#include <vector>
#include "button.h"

enum menuStates{MENU,WRITING_NAME,RULES,MUTE_TOGGLE,LEADERBOARD,PLAY};
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
	void setExit(void);
	button * getButtonReference(int index);
	std::vector<std::string> getLeadreboardInfo();
	unsigned int getNumberOfButtons(void);
	std::vector<button> & getButtonsVector(void);
	std::string & getName(void);
private:
	std::string bakcUpFile;
	std::string leaderboardFile;
	int state;
	bool workingIp;
	std::string name;
	std::string ip;
	std::vector<button> botones;
	bool exit;
};

