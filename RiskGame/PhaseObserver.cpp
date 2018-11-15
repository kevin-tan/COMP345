#include "stdafx.h"
#include "PhaseObserver.h"

void PhaseObserver::update() {
	using namespace std;
	cout << "\n----------------------- Phase viewer -----------------------" << endl;
	cout << subject->get_state() << endl;
}

PhaseObserver::~PhaseObserver() = default;

PhaseObserver::PhaseObserver(ISubject* subject) : IObserver(subject) {
	// No-op
}

