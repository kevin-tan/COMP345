#include "stdafx.h"
#include "algorithm"
#include "Subject.h"
ISubject::ISubject() : phase_state(nullptr) {
}

std::string ISubject::get_state() {
	return *phase_state;
}

void ISubject::set_state(std::string* state){
	phase_state = state;
}

void ISubject::add_listener(IObserver* ob) {
	std::cout << observers.size();
	observers.push_back(ob);
}

void ISubject::remove_listener(IObserver* ob) {
	observers.erase(std::remove(observers.begin(), observers.end(), ob), observers.end());
}

void ISubject::notify_all() {
	for (IObserver* ob : observers) {
		ob->update();
	}
}
ISubject::~ISubject() {
	for (int i = 0; i < observers.size(); ++i)
		observers[i] = nullptr;
	if (phase_state != nullptr)
		phase_state = nullptr;
}
