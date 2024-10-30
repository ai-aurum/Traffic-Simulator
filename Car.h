// Car.h
#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
private:
	// DATA MEMBERS
	string color;
public:
	// CONSTRUCTORS
	Car();
	Car(Place* loc, float speed, float weight, char dir, vector<Place*> places, string color);
	Car(Car const& og);
	~Car();


	// ACCESSOR MEMBER FUNCTIONS
	string getColor() const;

	// MODIFICATION MEMBER FUNCTIONS
	void setColor(string color);

	// OTHER
	virtual void printVehicle() const;
};

#endif
