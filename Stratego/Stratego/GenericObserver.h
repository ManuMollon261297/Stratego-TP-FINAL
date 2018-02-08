#pragma once


class GenericObserver
{
public:
	virtual ~GenericObserver();
	virtual void update();
};