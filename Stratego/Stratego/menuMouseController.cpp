#include "menuMouseController.h"
#include "pos.h"





menuMouseController::menuMouseController(MenuModel * p2menuModel_, dataButtonsPos & dataButtonsPos_)
{
	p2menuModel = p2menuModel_;
	dataButtons = dataButtonsPos_;
}

mouseMenuEvent menuMouseController::shape(int x, int y)
{
	bool butonFounded = false;
	mouseMenuEvent ret;
	ret.botonTouched = -1;
	for (int i = 0; (i < p2menuModel->getNumberOfButtons()) && (!butonFounded) ; i++)
	{
		if (p2menuModel->getButtonsVector()[i].isTouched(x, y))
		{
			ret.botonTouched = p2menuModel->getButtonsVector()[i].getIndex();
			butonFounded = true;
		}
	}
	return ret;
}

void menuMouseController::refreshButtons(void)
{
	p2menuModel->deleteButtons();
	button play_b(PLAY_B, dataButtons.ll_play, dataButtons.hr_play);
	button help_b(HELP_B, dataButtons.ll_help, dataButtons.hr_help);
	button leaderboard_b(LEADERBOARD_B, dataButtons.ll_leaderboard, dataButtons.hr_leaderboard);
	button sound_b(SOUND_B, dataButtons.ll_sound, dataButtons.hr_sound);
	button goback_b(GOBACK_B, dataButtons.ll_goback, dataButtons.hr_goback);

	switch (p2menuModel->getState())
	{
		case MENU:
			p2menuModel->pushButton(play_b);
			p2menuModel->pushButton(help_b);
			p2menuModel->pushButton(leaderboard_b);
			p2menuModel->pushButton(sound_b);
			
		case RULES:
		case LEADERBOARD:
			p2menuModel->pushButton(goback_b);
			break;

	}
}

menuMouseController::~menuMouseController()
{
}
