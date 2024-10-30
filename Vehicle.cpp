// Vehicle.cpp
#include "Vehicle.h"

// Default constructor
Vehicle::Vehicle() {
	loc = NULL;
	speed = 0;
	weight = 0;
}

// Init constructor
Vehicle::Vehicle(Place* loc, float speed, float weight, char dir, vector<Place*> places) {
	this->loc = loc;
	this->speed = speed;
	this->weight = weight;
	this->dir = dir;
	this->places = places;
}

// Copy constructor
Vehicle::Vehicle(Vehicle const& og) {
	this-> loc = og.loc;
	this->speed = og.speed;
	this->weight = og.weight;
	this->dir = og.dir;
	this->places = og.places;
}

// Destructor
Vehicle::~Vehicle() {}

// ACCESSOR MEMBER FUNCTIONS
Place* Vehicle::getLoc() const {
	return loc;
}

float Vehicle::getSpeed() const {
	return speed;
}

float Vehicle::getWeight() const {
	return weight;
}

char Vehicle::getDir() const {
	return dir;
}

vector<Place*> Vehicle::getPlaces() const {
	return places;
}

// MODIFICATION MEMBER FUNCTIONS
void Vehicle::setLoc(Place* loc) {
	this->loc = loc;
}

void Vehicle::setSpeed(float speed) {
	this->speed = speed;
}

void Vehicle::setWeight(float weight) {
	this->weight = weight;
}

void Vehicle::setDir(char dir) {
	this->dir = dir;
}

void Vehicle::setPlaces(vector<Place*> places) {
	this->places = places;
	setLoc(places[0]);
}

// OTHER
void Vehicle::printVehicle() const {}

