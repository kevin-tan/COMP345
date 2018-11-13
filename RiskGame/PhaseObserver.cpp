#include "stdafx.h"
#include "PhaseObserver.h"

void PhaseObserver::update() {
	using namespace std;
	cout << "\n----------------------- Phase viewer -----------------------" << endl;
	cout << subject->get_state() << endl;
}

IObserver::~IObserver() {
	delete subject;
}

PhaseObserver::PhaseObserver(ISubject* subject) : IObserver(subject){
	// No-op
}

