#pragma once


class GenericObserver
{
public:
	GenericObserver();
	virtual ~GenericObserver();
	virtual void update();
};