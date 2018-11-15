#include "stdafx.h"
#include "algorithm"
#include "Subject.h"

ISubject::ISubject() : phase_state(nullptr) {
	this->observers = new std::vector<IObserver*>();
}

std::string ISubject::get_state() {
	return *phase_state;
}

void ISubject::set_state(std::string* state){
	this->phase_state = state;
}

void ISubject::add_listener(IObserver* ob) {
	this->observers->push_back(ob);
}

void ISubject::remove_listener(IObserver* ob) {
	observers->erase(std::remove(observers->begin(), observers->end(), ob), observers->end());
}

void ISubject::notify_all() {
	for (IObserver* ob : *observers) {
		ob->update();
	}
}
ISubject::~ISubject() {
	for (IObserver* ob : *observers) {
		delete ob;
	}
	delete observers;
	delete phase_state;
}
