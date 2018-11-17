#include "stdafx.h"
#include "Observer.h"
#include "Subject.h"

IObserver::IObserver(ISubject* subject) : subject(subject) {
	subject->add_listener(this);
}
IObserver::~IObserver() {
	delete subject;
}
