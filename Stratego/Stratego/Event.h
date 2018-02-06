#pragma once

enum ev { NET, GRAPHICS, KEYBOARD, MOUSE, SOUND, TIMER, OTHER};

class GenericEvent
{
public:
	virtual unsigned int GetEvent(void);
	virtual void SetEvent(unsigned int);
	virtual char GetUd(void);
	virtual void SetUd(char);

protected:
	ev eventType;
	char ud;					//ver si se modifica (info del evento)
};