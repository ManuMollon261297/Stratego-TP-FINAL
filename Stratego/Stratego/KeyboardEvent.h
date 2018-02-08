#pragma once

#include "Event.h"
#include <allegro5\allegro.h>

class KeyboardEvent : public GenericEvent
{
public:
	KeyboardEvent(ALLEGRO_KEYBOARD_EVENT ev);
	~KeyboardEvent();

	virtual unsigned int GetEvent(void)const;
	virtual void SetEvent(unsigned int);

	ALLEGRO_KEYBOARD_EVENT GetAlEv(void)const;
	unsigned char getKey(void)const;
	bool GetBloqMayus(void)const;
	
private:
	unsigned char key;
	ALLEGRO_KEYBOARD_EVENT al_key_ev;
	bool bloqMayus; //Mayuscula o no.
	void ConvertToAscii(int ev_key);
};