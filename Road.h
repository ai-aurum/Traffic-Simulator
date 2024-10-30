// Road.h
#ifndef ROAD_H
#define ROAD_H

#include <iostream>
#include <vector>
#include "Place.h"

class Road {
private:
	// DATA MEMBER
	vector<Place*> lane;
public:
	// CONSTRUCTORS
	Road();
	Road(int x[], int y[], int nplaces, int direction);

	// ACCESSOR MEMBER FUNCTIONS
	vector<Place*> getLane() const;

	// MODIFICATION MEMBER FUNCTIONS
	void setLane(int x[], int y[], int nplaces, int direction);
};

#endif
