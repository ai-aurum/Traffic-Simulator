// Place.cpp
#include "Place.h"

// Default constructor
Place::Place() {
	vpoint = NULL;
}

// Init-Coordinate constructor
Place::Place(pair<int, int> &loc) {
	this->loc = loc;
}

// Copy-Constructor
Place::Place(Place const &og) {
	nor = og.nor;
	sou = og.sou;
	eas = og.eas;
	wes = og.wes;
	loc = og.loc;
}

// Destructor
Place::~Place() {}

// ACCESSOR MEMBER FUNCTIONS
Place* Place::getNor() const {
	return nor;
}

Place* Place::getSou() const {
	return sou;
}

Place* Place::getEas() const {
	return eas;
}

Place* Place::getWes() const {
	return wes;
}

pair<int, int> Place::getLoc() const {
	return loc;
}

Vehicle* Place::getVehicle() const {
	return vpoint;
}

bool Place::isOccupied() const {
	return (vpoint != NULL);
}

// MODIFICATION MEMBER FUNCTIONS
void Place::setNor(Place* nor) {
	this->nor = nor;
}

void Place::setSou(Place* sou) {
	this->sou = sou;
}

void Place::setEas(Place* eas) {
	this->eas = eas;
}

void Place::setWes(Place* wes) {
	this->wes = wes;
}

void Place::setLoc(pair<int, int>& loc) {
	this->loc = loc;
}

void Place::setVehicle(Vehicle* vpoint) {
	this->vpoint = vpoint;
}
