// Vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H

#include "Place.h"

class Vehicle {
private:
	// DATA MEMBERS
	Place* loc;
	float speed;
	float weight;
	char dir;
	vector<Place*> places;

public:
	// CONSTRUCTORS
	Vehicle();
	Vehicle(Place* loc, float speed, float weight, char dir, vector<Place*> places);
	Vehicle(Vehicle const& og);
	virtual ~Vehicle();

	// ACCESSOR MEMBER FUNCTIONS
	Place* getLoc() const;
	float getSpeed() const;
	float getWeight() const;
	char getDir() const;
	vector<Place*> getPlaces() const;

	// MODIFICATION MEMBER FUNCTIONS
	void setLoc(Place* location);
	void setSpeed(float speed);
	void setWeight(float weight);
	void setDir(char dir);
	void setPlaces(vector<Place*> places);

	// OTHER
	virtual void printVehicle() const;
	void move(int direction);
};

#endif