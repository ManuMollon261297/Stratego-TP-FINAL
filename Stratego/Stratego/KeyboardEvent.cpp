#include "KeyboardEvent.h"

#define ASCII_BACKSPACE 8
#define ASCII_SPACE 32
KeyboardEvent::KeyboardEvent(ALLEGRO_KEYBOARD_EVENT ev)
{
	eventType = KEYBOARD;
	al_key_ev = ev;
	/*
	ConvertToAscii(ev.keycode);
	if(ev.modifiers == ALLEGRO_KEYMOD_CAPSLOCK)
	{
		bloqMayus = true;
	}
	*/
}


KeyboardEvent::~KeyboardEvent()
{

}

unsigned int KeyboardEvent::GetEvent(void)const
{
	return eventType;
}

void KeyboardEvent::SetEvent(unsigned int newEv)
{
	eventType = (ev)newEv;
}

unsigned char KeyboardEvent::getKey(void)const
{
	return key;
}

void KeyboardEvent::ConvertToAscii(int ev_key)
{
	if ((ev_key >= ALLEGRO_KEY_A) && (ev_key <= ALLEGRO_KEY_Z))
	{
		key = (ev_key - (ALLEGRO_KEY_A)+ 'a'); //Si es una letra imprimible
	}
	else if ((ev_key >= ALLEGRO_KEY_0) && (ev_key <= ALLEGRO_KEY_9))
	{
		key = (ev_key - (ALLEGRO_KEY_0)+'0'); //si es un numero imprimible.
	}
	else //Otros casos posibles.
	{
		switch (ev_key)
		{
		case ALLEGRO_KEY_BACKSPACE:
			key = ASCII_BACKSPACE;
			break;
		case ALLEGRO_KEY_SPACE:
			key = ASCII_SPACE;
			break;
		default:
			key = '\0'; //Significa que no haga nada.
		}
	}
}


bool KeyboardEvent::GetBloqMayus(void)const
{
	return bloqMayus;
}

ALLEGRO_KEYBOARD_EVENT KeyboardEvent::GetAlEv(void)const
{
	return al_key_ev;
}
