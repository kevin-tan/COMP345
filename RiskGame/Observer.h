#pragma once
#include "stdafx.h"

class ISubject;

class IObserver {
protected:
	ISubject * subject;
	IObserver(ISubject* subject);
public:
	virtual ~IObserver();
	virtual void update() = 0;
};
