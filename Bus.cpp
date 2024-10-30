// Bus.cpp
#include "Bus.h"

// Default constructor
Bus::Bus() : Vehicle() {
	name = "N/A";
	occup = 0;
}

// Init constructor
Bus::Bus(Place* loc, float speed, float weight, char dir, vector<Place*> places, string name, int occup)
	: Vehicle(loc, speed, weight, dir, places) {
	this->name= name;
	this->occup = occup;
}

// Copy constructor
Bus::Bus(Bus const& og)
	: Vehicle(og) {
	this->name = og.name;
	this->occup = og.occup;
}

// Destructor
Bus::~Bus() {};

// ACCESSOR MEMBER FUNCTIONS
string Bus::getName() const {
	return name;
}

int Bus::getOccup() const {
	return occup;
}

// MODIFICATION MEMBER FUNCTIONS
void Bus::setName(string name) {
	this->name = name;
}

void Bus::setOccup(int occup) {
	this->occup= occup;
}

// OTHER
void Bus::printVehicle() const {
	cout << "B";
}