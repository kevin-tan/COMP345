#include "stdafx.h"
#include "Observer.h"
#include "Subject.h"

IObserver::IObserver(ISubject* subject) : subject(subject) {
	// No-op
}
IObserver::~IObserver() {
	delete subject;
}
