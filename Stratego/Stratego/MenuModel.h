#pragma once
#include <string>
#include <vector>
#include "GenericModel.h"
#include "button.h"

enum menuStates{MENU,WRITING_NAME,CONNECTING,RULES,MUTE_TOGGLE,LEADERBOARD,PLAY};
class MenuModel : public GenericModel
{
public:
	MenuModel();
	virtual ~MenuModel();
	int getState();
	void setState(int state_);
	bool getWorkingIp();
	void setWorkingIp(bool isIp);
	void addCharToWorkingString(char a);
	void deleteCharToWorkingString();
	void pushButton(button b);
	void deleteButtons();
	void setExit(void);
	void toggleSound();
	bool isMuteOn();
	bool GetExit(void)const;
	button * getButtonReference(int index);
	std::vector<std::string> getLeadreboardInfo();
	unsigned int getNumberOfButtons(void);
	std::vector<button> & getButtonsVector(void);
	std::string & getName(void);
	std::string getMessage(void);
	void setMessage(std::string);

private:
	std::string bakcUpFile;
	std::string leaderboardFile;
	int state;
	bool workingIp;
	std::string name;
	std::string ip;
	std::string message;
	std::vector<button> botones;
	bool exit;
	bool muteOn;
};

