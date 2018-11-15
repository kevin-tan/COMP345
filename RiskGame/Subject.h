#pragma once

#include "stdafx.h"
#include <vector>
#include "Observer.h"

class ISubject{
protected:
	ISubject();
	std::string* phase_state;
	std::vector<IObserver*> observers;
public:
	virtual ~ISubject();
	virtual void add_listener(IObserver* ob);
	virtual void remove_listener(IObserver* ob);
	virtual void notify_all();
	virtual std::string get_state();
	virtual void set_state(std::string* state);
};
