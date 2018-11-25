#include "stdafx.h"
#include "Observer.h"
#include "Subject.h"

IObserver::IObserver(ISubject* subject) : subject(subject) {
}
IObserver::~IObserver() {
}
