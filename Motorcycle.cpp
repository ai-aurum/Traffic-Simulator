// Motorcycle.cpp
#include "Motorcycle.h"

// Default constructor
Motorcycle::Motorcycle() : Vehicle() {
	name = "N/A";
}

// Init constructor
Motorcycle::Motorcycle(Place* loc, float speed, float weight, char dir, vector<Place*> places, string name)
	: Vehicle(loc, speed, weight, dir, places) {
	this->name = name;
}

// Copy constructor
Motorcycle::Motorcycle(Motorcycle const& og)
	: Vehicle(og) {
	this->name = og.name;
}

// Destructor
Motorcycle::~Motorcycle() {};

// ACCESSOR MEMBER FUNCTIONS
string Motorcycle::getName() const {
	return name;
}

// MODIFICATION MEMBER FUNCTIONS
void Motorcycle::setName(string name) {
	this->name = name;
}

// OTHER
void Motorcycle::printVehicle() const {
	cout << "M";
}
