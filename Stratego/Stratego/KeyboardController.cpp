#include "KeyboardController.h"

KeyboardController::KeyboardController(MenuModel * mm, ALLEGRO_EVENT_QUEUE * queue_, unsigned int maxIp, unsigned int maxName)
{
	initOk = true;

	pMenuModel = mm;
	IpMax = maxIp;
	NameMax = maxName;

	IpCount = 0;
	NameCount = 0;
	bloqMayus = false;

	/*
	queue = al_create_event_queue();

	if (!queue)
	{
		initOk = false;
	}
	al_register_event_source(queue, al_get_display_event_source(display));
	*/

	queue = queue_;

	if (!al_install_keyboard())
	{
		initOk = false;
	}
	al_register_event_source(queue, al_get_keyboard_event_source());
}

void KeyboardController::takeEvent(GenericEvent * genEv)
{
	KeyboardEvent * keyEv = (KeyboardEvent *) genEv;
	unsigned char butonPressed = 0;

	if (al_get_next_event(queue, keyEv->getAlEv) && ( keyEv->getAlEv->type == ALLEGRO_EVENT_KEY_DOWN))
	{
		butonPressed = keyEv->getAlEv->keyboard.keycode;

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
	//delete pMenuModel;
	al_destroy_event_queue(queue);
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