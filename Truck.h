// Truck.h
#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
private:
	// DATA MEMBERS
	string color;
	float weight_trailer;
public:
	// CONSTRUCTORS
	Truck();
	Truck(Place* loc, float speed, float weight, char dir, vector<Place*> places, string color, float weight_trailer);
	Truck(Truck const& og);
	~Truck();


	// ACCESSOR MEMBER FUNCTIONS
	string getColor() const;
	float getWeightTrailer() const;

	// MODIFICATION MEMBER FUNCTIONS
	void setColor(string color);
	void setWeightTrailer(float weight_trailer);

	// OTHER
	virtual void printVehicle() const;
};

#endif