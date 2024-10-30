// Car.cpp
#include "Car.h"

// Default constructor
Car::Car() : Vehicle() {
	color = "N/A";
}

// Init constructor
Car::Car(Place* loc, float speed, float weight, char dir, vector<Place*> places, string color)
	: Vehicle(loc, speed, weight, dir, places) {
	this->color = color;
}

// Copy constructor
Car::Car(Car const& og)
	: Vehicle(og) {
	this->color = og.color;
}

// Destructor
Car::~Car() {};

// ACCESSOR MEMBER FUNCTIONS
string Car::getColor() const {
	return color;
}

// MODIFICATION MEMBER FUNCTIONS
void Car::setColor(string color) {
	this->color = color;
}

// OTHER
void Car::printVehicle() const {
	cout << "C";
}
