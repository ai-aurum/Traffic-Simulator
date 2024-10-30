// Motorcylce.h
#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

class Motorcycle : public Vehicle {
private:
	// DATA MEMBERS
	string name;
public:
	// CONSTRUCTORS
	Motorcycle();
	Motorcycle(Place* loc, float speed, float weight, char dir, vector<Place*> places, string name);
	Motorcycle(Motorcycle const& og);
	~Motorcycle();

	// ACCESSOR MEMBER FUNCTIONS
	string getName() const;

	// MODIFCATION MEMBER FUNCTIONS
	void setName(string name);

	// OTHER
	virtual void printVehicle() const;
};

#endif