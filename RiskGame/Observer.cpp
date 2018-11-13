#include "stdafx.h"
#include "Observer.h"

IObserver::IObserver(ISubject* subject) : subject(subject) {
	// No-op
}