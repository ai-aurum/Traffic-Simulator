// Road.cpp
#include "Road.h"

// CONSTRUCTORS
Road::Road() {};

Road::Road(int x[], int y[], int nplaces, int direction) {
	// Create the first place in the road
	pair<int, int> firstLoc(x[0], y[0]);
	Place* tempPlace = new Place(firstLoc);
	tempPlace->setVehicle(NULL);
	lane.push_back(tempPlace);


	for (int i = 1; i < nplaces; i++) {
		pair<int, int> tempLoc(x[i], y[i]);
		tempPlace = new Place(tempLoc);
		tempPlace->setVehicle(NULL);
		lane.push_back(tempPlace);

		switch (direction) {
		case 0:		lane[i - 1]->setNor(tempPlace);
					break;

		case 1:		lane[i - 1]->setSou(tempPlace);
					break;

		case 2:		lane[i - 1]->setEas(tempPlace);
					break;

		case 3:		lane[i - 1]->setWes(tempPlace);
					break;
		}
	}
}

// ACCESSOR MEMBER FUNCTIONS
vector<Place*> Road::getLane() const {
	return lane;
}

// MODIFICATION MEMBER FUNCTIONS
void Road::setLane(int x[], int y[], int nplaces, int direction) {
	lane.clear();
	// Create the first place in the road
	pair<int, int> firstLoc(x[0], y[0]);
	Place* tempPlace = new Place(firstLoc);
	tempPlace->setVehicle(NULL);
	lane.push_back(tempPlace);

	for (int i = 1; i < nplaces; i++) {
		pair<int, int> tempLoc(x[i], y[i]);
		tempPlace = new Place(tempLoc);
		tempPlace->setVehicle(NULL);
		lane.push_back(tempPlace);

		switch (direction) {
		case 0:		lane[i - 1]->setNor(tempPlace);
			break;

		case 1:		lane[i - 1]->setSou(tempPlace);
			break;

		case 2:		lane[i - 1]->setEas(tempPlace);
			break;

		case 3:		lane[i - 1]->setWes(tempPlace);
			break;
		}
	}
}