// Truck.cpp
#include "Truck.h"

// Default constructor
Truck::Truck() : Vehicle() {
	color = "N/A";
	weight_trailer = 0;
}

// Init constructor
Truck::Truck(Place* loc, float speed, float weight, char dir, vector<Place*> places, string color, float weight_trailer)
	: Vehicle(loc, speed, weight, dir, places) {
	this->color = color;
	this->weight_trailer = weight_trailer;
}

// Copy constructor
Truck::Truck(Truck const& og)
	: Vehicle(og) {
	this->color = og.color;
	this->weight_trailer = og.weight_trailer;
}

// Destructor
Truck::~Truck() {};

// ACCESSOR MEMBER FUNCTIONS
string Truck::getColor() const {
	return color;
}

float Truck::getWeightTrailer() const {
	return weight_trailer;
}

// MODIFICATION MEMBER FUNCTIONS
void Truck::setColor(string color) {
	this->color = color;
}

void Truck::setWeightTrailer(float weight_trailer) {
	this->weight_trailer = weight_trailer;
}

// OTHER
void Truck::printVehicle() const {
	cout << "T";
}