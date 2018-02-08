#include "KeyboardController.h"

KeyboardController::KeyboardController(MenuModel * mm, unsigned int maxIp, unsigned int maxName)
{
	initOk = true;

	pMenuModel = mm;
	IpMax = maxIp;
	NameMax = maxName;

	IpCount = 0;
	NameCount = 0;
	bloqMayus = false;

	
	
}

void KeyboardController::dispatch(GenericEvent& genEv)
{
	if ( (genEv.GetEvent() == KEYBOARD)&&(pMenuModel->getState() == WRITING_NAME))
	{
		KeyboardEvent& keyEv = (KeyboardEvent&)genEv;
		int butonPressed = (keyEv.GetAlEv().keycode);


		if ((butonPressed >= ALLEGRO_KEY_A) && (butonPressed <= ALLEGRO_KEY_Z))		//Es una letra de la A a la Z
		{
			if (validateAdd())
			{
				ALLEGRO_KEYBOARD_STATE key_state;
				al_get_keyboard_state(&key_state);

				bool mayusShift = (al_key_down(&key_state, ALLEGRO_KEY_LSHIFT) ||
					al_key_down(&key_state, ALLEGRO_KEY_RSHIFT));
				//Chequeo si se está tocando el shift izquierdo o derecho

				if ((mayusShift || bloqMayus) && !(mayusShift && bloqMayus))		//Chequeo si bloq mayus ya estaba activado
					pMenuModel->addCharToWorkingString(butonPressed + 64);			 //Le sumo un desfasaje para pasarlo a ascii (en mayuscula)

				else
					pMenuModel->addCharToWorkingString(butonPressed + 96);			//Le sumo un desfasaje para pasarlo a ascii (en minuscula)
			}
		}

		else if ((butonPressed >= ALLEGRO_KEY_0) && (butonPressed <= ALLEGRO_KEY_9))
		{
			if (validateAdd())
				pMenuModel->addCharToWorkingString(butonPressed + 21);				//Le sumo un desfasaje para pasarlo a ascii
		}

		else if (butonPressed == ALLEGRO_KEY_SPACE)
		{
			if (validateAdd())
				pMenuModel->addCharToWorkingString(' ');
		}
		else if ((butonPressed == ALLEGRO_KEY_TAB) || (butonPressed == ALLEGRO_KEY_ENTER))
			pMenuModel->setWorkingIp(!(pMenuModel->getWorkingIp()));

		else if (butonPressed == ALLEGRO_KEY_CAPSLOCK)
			bloqMayus = !bloqMayus;

		else if ((butonPressed == ALLEGRO_KEY_BACKSPACE) && (validateSub()))
			pMenuModel->deleteCharToWorkingString();
	}
}
	


KeyboardController::~KeyboardController()
{
	
}

bool KeyboardController::validateAdd()
{
	bool ret = false;
	if (pMenuModel->getWorkingIp())
	{
		if (IpCount < IpMax)
		{
			IpCount++;
			ret = true;
		}
	}
	else
	{
		if (NameCount < NameMax)
		{
			NameCount++;
			ret = true;
		}
	}
	
	return ret;
}

bool KeyboardController::validateSub()
{
	bool ret = false;
	if (pMenuModel->getWorkingIp())
	{
		if (IpCount > 0)
		{
			IpCount--;
			ret = true;
		}
	}
	else
	{
		if (NameCount > 0)
		{
			NameCount--;
			ret = true;
		}
	}

	return ret;
}

