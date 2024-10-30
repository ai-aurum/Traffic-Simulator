// Bus.h
#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"

class Bus : public Vehicle {
private:
	// DATA MEMBERS
	string name;
	int occup;
public:
	// CONSTRUCTORS
	Bus();
	Bus(Place* loc, float speed, float weight, char dir, vector<Place*> places, string name, int num_pasgn);
	Bus(Bus const& og);
	~Bus();

	// ACCESSOR MEMBER FUNCTIONS
	string getName() const;
	int getOccup() const;

	// MODIFCATION MEMBER FUNCTIONS
	void setName(string name);
	void setOccup(int occup);

	// OTHER
	virtual void printVehicle() const;

};

#endif
