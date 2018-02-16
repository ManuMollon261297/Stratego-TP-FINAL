#pragma once

enum ev { NET, GRAPHICS, KEYBOARD, MOUSE, SOUND, TIMER, OTHER};

class GenericEvent
{
public:
	virtual unsigned int GetEvent(void);
	virtual void SetEvent(unsigned int);

protected:
	ev eventType;
};