#pragma once


class GenericObserver
{
public:
	GenericObserver();
	GenericObserver(GenericObserver&&);
	virtual ~GenericObserver();
	virtual void update();
};