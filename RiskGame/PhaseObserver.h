#pragma once
#include "Observer.h"
#include "Subject.h"

class PhaseObserver : public IObserver {
public:
	PhaseObserver(ISubject* subject);
	void update() override;
};