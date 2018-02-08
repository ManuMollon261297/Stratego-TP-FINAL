#pragma once
#include "Event.h"

class GenericController
{
public:
	virtual void dispatch(GenericEvent&);
};