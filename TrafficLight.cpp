// TrafficLight.cpp
#include <iostream>
#include "TrafficLight.h"
using namespace std;

// Default constructor
TrafficLight::TrafficLight() {
	this->duration = 0;
	this->yellow = 0;
	this->flow = false;
}

// Init constructor
TrafficLight::TrafficLight(int duration, int yellow, bool flow) {
	this->duration = duration;
	this->yellow = yellow;
	this->flow = flow;
}

// Copy constructor
TrafficLight::TrafficLight(TrafficLight const& og) {
	this->duration = og.duration;
	this->yellow = og.yellow;
	this->flow = og.flow;
}

TrafficLight::~TrafficLight() {};

// ACCESSOR MEMBER FUNCTIONS
int TrafficLight::getDuration() const {
	return duration;
}

int TrafficLight::getYellow() const {
	return yellow;
}

bool TrafficLight::getFlow() const {
	return flow;
}

int TrafficLight::getElapsed() const {
	return elapsed;
}

// MODFICATION MEMBER FUNCTIONS
void TrafficLight::setDuration(int duration) {
	this->duration = duration;
}

void TrafficLight::setYellow(int yellow) {
	this->yellow = yellow;
}

void TrafficLight::setFlow(bool flow) {
	this->flow = flow;
}

void TrafficLight::switchFlow() {
	flow = !flow;
}

void TrafficLight::tick() {
	elapsed++;
}