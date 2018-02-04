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
	button confirm_b(CONFIRM_B, dataButtons.ll_confirm, dataButtons.hr_confirm);

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
			p2menuModel->pushButton(sound_b);
			break;
		case WRITING_NAME:
			p2menuModel->pushButton(goback_b);
			p2menuModel->pushButton(confirm_b);
			p2menuModel->pushButton(sound_b);

	}
}

void menuMouseController::dispatch(mouseMenuEvent & menuEvMouse)
{
	if (p2menuModel->getState() != state)
	{
		state = p2menuModel->getState();
		refreshButtons();
	}
	switch (menuEvMouse.botonTouched)
	{
		case PLAY_B:
			state = WRITING_NAME;
			break;
		case HELP_B:
			state = RULES;
			break;
		case GOBACK_B:
			state = MENU;
			break;
		case LEADERBOARD_B:
			state = LEADERBOARD;
			break;
		case SOUND_B:
			
			break;
		case CONFIRM_B:
			if ((p2menuModel->getName().size() > 0) && (p2menuModel->getName().size() < 12))
			{
				p2menuModel->setExit();
			}
			break;
	}
}

menuMouseController::~menuMouseController()
{
}
