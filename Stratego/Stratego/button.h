#pragma once
#include "pos.h"

#define PLACE_READY_B 1
#define PLAY_AGAIN_B 2
#define GAME_OVER_B 3
#define PLAY_B 4
#define HELP_B 5
#define GOBACK_B 6
#define LEADERBOARD_B 7
#define SOUND_B 8

typedef struct
{
	pos ll_play;
	pos hr_play;
	pos ll_help;
	pos hr_help;
	pos ll_goback;
	pos hr_goback;
	pos ll_leaderboard;
	pos hr_leaderboard;
	pos ll_sound;
	pos hr_sound;
}dataButtonsPos;

class button
{
public:
	button(int index_, pos LL, pos HR);
	void press();
	void unpress();
	bool getPressStatus();
	int getIndex();
	bool isTouched(double x, double y);
	~button();
private:
	pos verticeLL; //low left
	pos verticeHR; //high right
	int index;
	bool pressed;
};

