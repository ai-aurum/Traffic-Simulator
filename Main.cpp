// Main.cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include "Place.h"
#include "Road.h"
#include "Car.h"
#include "Truck.h"
#include "Bus.h"
#include "Motorcycle.h"
#include "TrafficLight.h"
using namespace std;

#define ROAD_LEN 50

void print_traffic(vector<Road> const& lanes);

int main() {
	// First, create and initialize the roads
	// Directions:
	// 0 - North
	// 1 - South
	// 2 - East
	// 3 - West
	vector<Road> lanes;
	int x[ROAD_LEN];
	int y[ROAD_LEN];

	for (int i = 0; i < ROAD_LEN; i++) {	// Creating north bound
		x[i] = ROAD_LEN / 2;
		y[i] = ROAD_LEN - i - 1;
	}
	Road norBound(x, y, ROAD_LEN, 0);
	lanes.push_back(norBound);

	for (int i = 0; i < ROAD_LEN; i++) {	// Creating south bound
		x[i] = ROAD_LEN / 2 - 1;
		y[i] = i;
	}
	Road souBound(x, y, ROAD_LEN, 1);
	lanes.push_back(souBound);

	for (int i = 0; i < ROAD_LEN; i++) {	// Creating east bound
		x[i] = i;
		y[i] = ROAD_LEN / 2;
	}
	Road easBound(x, y, ROAD_LEN, 2);
	lanes.push_back(easBound);

	for (int i = 0; i < ROAD_LEN; i++) {	// Creating west bound
		x[i] = ROAD_LEN - i - 1;
		y[i] = ROAD_LEN / 2 - 1;
	}
	Road wesBound(x, y, ROAD_LEN, 3);
	lanes.push_back(wesBound);

	// Create four queues for each lane
	queue<Vehicle*> norQueue, souQueue, easQueue, wesQueue;
	
	// Reset random seed
	srand(time(0));

	// Now that roads are initialized, set up main loop to move cars
	// Each red light is 14 ticks, yellow is 6, green is therefore 8 (red - yellow)
	TrafficLight light(14, 6, true);
	int token = 1;
	int count = 160;
	int z = 0;
	while (z < count) {
		// Print out tick number
		cout << "Tick: " << light.getElapsed() << endl;

		// Determine light color, either green or yellow.
		// Green = tick is 0-7
		// Yellow = tick is 7-13
		string lightColor;
		if (light.getElapsed() % light.getDuration() <= 7) {
			lightColor = "green";

			// Switch flow if tick is 0
			if (light.getElapsed() % light.getDuration() == 0)
				light.switchFlow();
		}
		else {
			lightColor = "yellow";
		}

		// Queue size may change within respective for loops, so use 
		// variable to keep the size "static" until the end of each iteration of a 
		// lane movement (moving every car in a lane).
		int queueSize;

		// Determine the flow of traffic
		if (light.getFlow()) {	// (true) Flow is north/south
			// Print out light color
			cout << "The light is " << lightColor << " in the north-south direction." << endl;
			cout << "The light is red in the east-west direction." << endl;


			// Move cars in the north bound
			// Obtain vehicle at the front of the north queue
			Vehicle* norToMove;
			queueSize = norQueue.size();		// queue size may change within the for loop, so have variable to compensate
			for (int i = 0; i < queueSize; i++) {
				norToMove = norQueue.front();

				// Check if car is at the end of the road
				vector<Place*> occPlaces = norToMove->getPlaces();
				if (occPlaces[0]->getLoc().second == 0) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					norQueue.pop();
					norToMove->~Vehicle();
					continue;
				}
				// Move car if there is room ahead
				else if (occPlaces[0]->getLoc().second == 1
					|| (!occPlaces[0]->getNor()->isOccupied() && !occPlaces[0]->getNor()->getNor()->isOccupied())) {
					// If the light is yellow, dont move cars just before the intersection
					if (lightColor == "yellow" && occPlaces[0]->getLoc().second != ROAD_LEN / 2 + 1
						|| lightColor == "green") {

						// Update vehicle pointers in place objects
						occPlaces[0]->getNor()->setVehicle(norToMove);
						occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

						// Update place pointers in vehicle object
						for (int j = 0; j < occPlaces.size(); j++) {
							occPlaces[j] = occPlaces[j]->getNor();
						}
						norToMove->setPlaces(occPlaces);
					}
				}

				// Move vehicle to back of queue, whether it moved or not
				norQueue.push(norQueue.front());

				// Pop the nor queue
				norQueue.pop();
			}

			// Move cars in the south bound
			// Obtain vehicle at the front of the south queue
			Vehicle* souToMove;
			queueSize = souQueue.size();
			for (int i = 0; i < queueSize; i++) {
				souToMove = souQueue.front();
				// Check if car is at the end of the road
				vector<Place*> occPlaces = souToMove->getPlaces();
				if (occPlaces[0]->getLoc().second == ROAD_LEN - 1) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					souQueue.pop();
					souToMove->~Vehicle();
					continue;
				}
				// Move car if there is room
				else if (occPlaces[0]->getLoc().second == ROAD_LEN - 2
					|| (!occPlaces[0]->getSou()->isOccupied() && !occPlaces[0]->getSou()->getSou()->isOccupied())) {
					// If the light is yellow, dont move cars just before the intersection
					if (lightColor == "yellow" && occPlaces[0]->getLoc().second != ROAD_LEN / 2 - 2
						|| lightColor == "green") {

						// Update vehicle pointers in place objects
						occPlaces[0]->getSou()->setVehicle(souToMove);
						occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

						// Update place pointers in vehicle object
						for (int j = 0; j < occPlaces.size(); j++) {
							occPlaces[j] = occPlaces[j]->getSou();
						}
						souToMove->setPlaces(occPlaces);
					}
				}
				// Move vehicle to back of queue;
				souQueue.push(souQueue.front());

				// Pop sou queue
				souQueue.pop();
			}

			// Move cars in the east bound (red light)
			Vehicle* easToMove;
			queueSize = easQueue.size();
			for (int i = 0; i < queueSize; i++) {
				easToMove = easQueue.front();
				// Check if car is at the end of the road
				vector<Place*> occPlaces = easToMove->getPlaces();
				if (occPlaces[0]->getLoc().first == ROAD_LEN - 1) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					easQueue.pop();
					easToMove->~Vehicle();
					continue;
				}
				// Move car if there is room and is not at the intersection
				else if (occPlaces[0]->getLoc().first == ROAD_LEN - 2
					|| !(occPlaces[0]->getEas()->isOccupied() || occPlaces[0]->getEas()->getEas()->isOccupied())
						&& occPlaces[0]->getLoc().first != ROAD_LEN / 2 - 2) {
					// Update vehicle poitners in place objects
					occPlaces[0]->getEas()->setVehicle(easToMove);
					occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

					// Update place poitners in vehicle object
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j] = occPlaces[j]->getEas();
					}
					easToMove->setPlaces(occPlaces);
				}

				// Move vehicle to back of queue
				easQueue.push(easQueue.front());

				// Pop east queue
				easQueue.pop();
			}

			// Move cars in the west bound (red light)
			Vehicle* wesToMove;
			queueSize = wesQueue.size();
			for (int i = 0; i < queueSize; i++) {
				wesToMove = wesQueue.front();
				// Check if car is at the end of the road
				vector<Place*> occPlaces = wesToMove->getPlaces();
				if (occPlaces[0]->getLoc().first == 0) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					wesQueue.pop();
					wesToMove->~Vehicle();
					continue;
				}
				// Move car if there is room and is not at the intersection
				else if (occPlaces[0]->getLoc().first == 1
						|| !(occPlaces[0]->getWes()->isOccupied() || occPlaces[0]->getWes()->getWes()->isOccupied()) 
						&& occPlaces[0]->getLoc().first != ROAD_LEN / 2 + 1) {
					// Update vehicle poitners in place objects
					occPlaces[0]->getWes()->setVehicle(wesToMove);
					occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

					// Update place poitners in vehicle object
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j] = occPlaces[j]->getWes();
					}
					wesToMove->setPlaces(occPlaces);
				}

				// Move vehicle to back of queue
				wesQueue.push(wesQueue.front());

				// Pop west queue
				wesQueue.pop();
			}
		}
		else {	// Flow is east/west
			// Print out light color
			cout << "The light is red in the north-south direction." << endl;
			cout << "The light is " << lightColor << " in the east_west direction." << endl;

			// Move cars in the east bound
			// Obtain vehicle at the front of the east queue
			Vehicle* easToMove;
			queueSize = easQueue.size();
			for (int i = 0; i < queueSize; i++) {
				easToMove = easQueue.front();

				// Check if car is at the end of the road
				vector<Place*> occPlaces = easToMove->getPlaces();
				if (occPlaces[0]->getLoc().first == ROAD_LEN - 1) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					easQueue.pop();
					easToMove->~Vehicle();
					continue;
				}
				// Move car if there is room ahead
				else if (occPlaces[0]->getLoc().first == ROAD_LEN - 2
					|| (!occPlaces[0]->getEas()->isOccupied() && !occPlaces[0]->getEas()->getEas()->isOccupied())) {
					// If the light is yellow, dont move cars just before the intersection
					if (lightColor == "yellow" && occPlaces[0]->getLoc().first != ROAD_LEN / 2 - 2
						|| lightColor == "green") {

						// Update vehicle pointers in place objects
						occPlaces[0]->getEas()->setVehicle(easToMove);
						occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

						// Update place pointers in vehicle object
						for (int j = 0; j < occPlaces.size(); j++) {
							occPlaces[j] = occPlaces[j]->getEas();
						}
						easToMove->setPlaces(occPlaces);
					}
				}
				// Move vehicle to back of queue, whether it moved or not
				easQueue.push(easQueue.front());
				easQueue.pop();
			}

			// Move cars in the west bound
			// Obtain vehicle at the front of the west queue
			Vehicle* wesToMove;
			queueSize = wesQueue.size();
			for (int i = 0; i < queueSize; i++) {
				wesToMove = wesQueue.front();

				// Check if car is at the end of the road
				vector<Place*> occPlaces = wesToMove->getPlaces();
				if (occPlaces[0]->getLoc().first == 0) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					wesQueue.pop();
					wesToMove->~Vehicle();
					continue;
				}
				// Move car if there is room ahead
				else if (occPlaces[0]->getLoc().first == 1
					|| !(occPlaces[0]->getWes()->isOccupied() || occPlaces[0]->getWes()->getWes()->isOccupied())) {
					// If the light is yellow, dont move cars just before the intersection
					if (lightColor == "yellow" && occPlaces[0]->getLoc().first != ROAD_LEN / 2 + 1
						|| lightColor == "green") {

						// Update vehicle pointers in place objects
						occPlaces[0]->getWes()->setVehicle(wesToMove);
						occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

						// Update place pointers in vehicle object
						for (int j = 0; j < occPlaces.size(); j++) {
							occPlaces[j] = occPlaces[j]->getWes();
						}
						wesToMove->setPlaces(occPlaces);
					}
				}
				// Move vehicle to back of queue, whether it moved or not
				wesQueue.push(wesQueue.front());
				wesQueue.pop();
			}

			// Move cars in the north bound
			Vehicle* norToMove;
			queueSize = norQueue.size();
			for (int i = 0; i < queueSize; i++) {
				norToMove = norQueue.front();
				// Check if car is at the end of the road
				vector<Place*> occPlaces = norToMove->getPlaces();
				if (occPlaces[0]->getLoc().second == 0) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					norQueue.pop();
					norToMove->~Vehicle();
					continue;
				}
				// Move car if there is room and is not at the intersection
				else if (occPlaces[0]->getLoc().second == 1
					|| !(occPlaces[0]->getNor()->isOccupied() || occPlaces[0]->getNor()->getNor()->isOccupied()) 
						&& occPlaces[0]->getLoc().second != ROAD_LEN / 2 + 1) {
					// Update vehicle poitners in place objects
					occPlaces[0]->getNor()->setVehicle(norToMove);
					occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

					// Update place poitners in vehicle object
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j] = occPlaces[j]->getNor();
					}
					norToMove->setPlaces(occPlaces);
				}

				// Move vehicle to back of queue
				norQueue.push(norQueue.front());
				norQueue.pop();
			}

			// Move cars in the south bound
			Vehicle* souToMove;
			queueSize = souQueue.size();
			for (int i = 0; i < queueSize; i++) {
				souToMove = souQueue.front();
				// Check if car is at the end of the road
				vector<Place*> occPlaces = souToMove->getPlaces();
				if (occPlaces[0]->getLoc().second == ROAD_LEN - 1) {
					// Remove vehicle pointers
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j]->setVehicle(NULL);
					}
					// Delete vehicle
					souQueue.pop();
					souToMove->~Vehicle();
					continue;
				}
				// Move car if there is room and is not at the intersection
				else if (occPlaces[0]->getLoc().second == ROAD_LEN - 2
					|| !(occPlaces[0]->getSou()->isOccupied() || occPlaces[0]->getSou()->getSou()->isOccupied())
						&& occPlaces[0]->getLoc().second != ROAD_LEN / 2 - 2) {
					// Update vehicle poitners in place objects
					occPlaces[0]->getSou()->setVehicle(souToMove);
					occPlaces[occPlaces.size() - 1]->setVehicle(NULL);

					// Update place poitners in vehicle object
					for (int j = 0; j < occPlaces.size(); j++) {
						occPlaces[j] = occPlaces[j]->getSou();
					}
					souToMove->setPlaces(occPlaces);
				}

				// Move vehicle to back of queue
				souQueue.push(souQueue.front());
				souQueue.pop();
			}
		}
		

		// Randomly generate a car or bus
		for (int i = 0; i < 4; i++) {
			int prob = 6;
			int type_prob = 6;
			bool thereIsRoom = true;
			if (rand() % prob == 0) {	// Vehicle may be added
				// Determine the type of vehice to be generated
				int vtype = rand() % type_prob;
				if (vtype < 2) {	// Car
					switch (i) {		// Add car in respective direction
					case 0:
						// Determine if there is room for a car
						for (int j = 0; j < 3; j++) {
							if (norBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}
						// If there is room, generate a car
						if (thereIsRoom) {
							Car* newCar = new Car();
							vector<Place*> initPos;
							for (int j = 1; j >= 0; j--) {
								norBound.getLane()[j]->setVehicle(newCar);
								initPos.push_back(norBound.getLane()[j]);
							}
							newCar->setPlaces(initPos);
							norQueue.push(newCar);
						}
						break;
					case 1:
						// Determine if there is room for a car
						for (int j = 0; j < 3; j++) {
							if (souBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}
						// If there is room, generate a car
						if (thereIsRoom) {
							Car* newCar = new Car();
							vector<Place*> initPos;
							for (int j = 1; j >= 0; j--) {
								souBound.getLane()[j]->setVehicle(newCar);
								initPos.push_back(souBound.getLane()[j]);
							}
							newCar->setPlaces(initPos);
							souQueue.push(newCar);
						}
						break;
					case 2:
						// Determine if there is room for a car
						for (int j = 0; j < 3; j++) {
							if (easBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}
						// If there is room, generate a car
						if (thereIsRoom) {
							Car* newCar = new Car();
							vector<Place*> initPos;
							for (int j = 1; j >= 0; j--) {
								easBound.getLane()[j]->setVehicle(newCar);
								initPos.push_back(easBound.getLane()[j]);
							}
							newCar->setPlaces(initPos);
							easQueue.push(newCar);
						}
						break;
					case 3:
						// Determine if there is room for a car
						for (int j = 0; j < 3; j++) {
							if (wesBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}
						// If there is room, generate a car
						if (thereIsRoom) {
							Car* newCar = new Car();
							vector<Place*> initPos;
							for (int j = 1; j >= 0; j--) {
								wesBound.getLane()[j]->setVehicle(newCar);
								initPos.push_back(wesBound.getLane()[j]);
							}
							newCar->setPlaces(initPos);
							wesQueue.push(newCar);
						}
					}
					break;
				} 
				else if (vtype < 4) {	// Bus
					switch (i) {
					case 0:
						// Determine if there is room for a bus
						for (int j = 0; j < 7; j++) {
							if (norBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Bus* newBus = new Bus();
							vector<Place*> initPos;
							for (int j = 5; j >= 0; j--) {
								norBound.getLane()[j]->setVehicle(newBus);
								initPos.push_back(norBound.getLane()[j]);
							}
							newBus->setPlaces(initPos);
							norQueue.push(newBus);
						}
						break;
					case 1:
						// Determine if there is room for a bus
						for (int j = 0; j < 7; j++) {
							if (souBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Bus* newBus = new Bus();
							vector<Place*> initPos;
							for (int j = 5; j >= 0; j--) {
								souBound.getLane()[j]->setVehicle(newBus);
								initPos.push_back(souBound.getLane()[j]);
							}
							newBus->setPlaces(initPos);
							souQueue.push(newBus);
						}
						break;
					case 2:
						// Determine if there is room for a bus
						for (int j = 0; j < 7; j++) {
							if (easBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Bus* newBus = new Bus();
							vector<Place*> initPos;
							for (int j = 5; j >= 0; j--) {
								easBound.getLane()[j]->setVehicle(newBus);
								initPos.push_back(easBound.getLane()[j]);
							}
							newBus->setPlaces(initPos);
							easQueue.push(newBus);
						}
						break;
					case 3:
						// Determine if there is room for a bus
						for (int j = 0; j < 7; j++) {
							if (wesBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Bus* newBus = new Bus();
							vector<Place*> initPos;
							for (int j = 5; j >= 0; j--) {
								wesBound.getLane()[j]->setVehicle(newBus);
								initPos.push_back(wesBound.getLane()[j]);
							}
							newBus->setPlaces(initPos);
							wesQueue.push(newBus);
						}
						break;
					}
				}
				else if (vtype < 5) {	// Truck
					switch (i) {
					case 0:
						// Determine if there is room for a truck
						for (int j = 0; j < 6; j++) {
							if (norBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Truck* newTruck = new Truck();
							vector<Place*> initPos;
							for (int j = 4; j >= 0; j--) {
								norBound.getLane()[j]->setVehicle(newTruck);
								initPos.push_back(norBound.getLane()[j]);
							}
							newTruck->setPlaces(initPos);
							norQueue.push(newTruck);
						}
						break;
					case 1:
						// Determine if there is room for a truck
						for (int j = 0; j < 6; j++) {
							if (souBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Truck* newTruck = new Truck();
							vector<Place*> initPos;
							for (int j = 4; j >= 0; j--) {
								souBound.getLane()[j]->setVehicle(newTruck);
								initPos.push_back(souBound.getLane()[j]);
							}
							newTruck->setPlaces(initPos);
							souQueue.push(newTruck);
						}
						break;
					case 2:
						// Determine if there is room for a truck
						for (int j = 0; j < 6; j++) {
							if (easBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Truck* newTruck = new Truck();
							vector<Place*> initPos;
							for (int j = 4; j >= 0; j--) {
								easBound.getLane()[j]->setVehicle(newTruck);
								initPos.push_back(easBound.getLane()[j]);
							}
							newTruck->setPlaces(initPos);
							easQueue.push(newTruck);
						}
						break;
					case 3:
						// Determine if there is room for a truck
						for (int j = 0; j < 6; j++) {
							if (wesBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Bus* newBus = new Bus();
							vector<Place*> initPos;
							for (int j = 4; j >= 0; j--) {
								wesBound.getLane()[j]->setVehicle(newBus);
								initPos.push_back(wesBound.getLane()[j]);
							}
							newBus->setPlaces(initPos);
							wesQueue.push(newBus);
						}
						break;
					}
				}
				else {		// Motorcycle
					switch (i) {
					case 0:
						// Determine if there is room for a motorcycle
						for (int j = 0; j < 2; j++) {
							if (norBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Motorcycle* newMotorcycle = new Motorcycle();
							vector<Place*> initPos;
							norBound.getLane()[0]->setVehicle(newMotorcycle);
							initPos.push_back(norBound.getLane()[0]);
							newMotorcycle->setPlaces(initPos);
							norQueue.push(newMotorcycle);
						}
						break;
					case 1:
						// Determine if there is room for a motorcycle
						for (int j = 0; j < 2; j++) {
							if (souBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Motorcycle* newMotorcycle = new Motorcycle();
							vector<Place*> initPos;
							souBound.getLane()[0]->setVehicle(newMotorcycle);
							initPos.push_back(souBound.getLane()[0]);
							newMotorcycle->setPlaces(initPos);
							souQueue.push(newMotorcycle);
						}
						break;
					case 2:
						// Determine if there is room for a motorcycle
						for (int j = 0; j < 2; j++) {
							if (easBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Motorcycle* newMotorcycle = new Motorcycle();
							vector<Place*> initPos;
							easBound.getLane()[0]->setVehicle(newMotorcycle);
							initPos.push_back(easBound.getLane()[0]);
							newMotorcycle->setPlaces(initPos);
							easQueue.push(newMotorcycle);
						}
						break;
					case 3:
						// Determine if there is room for a motorcycle
						for (int j = 0; j < 2; j++) {
							if (wesBound.getLane()[j]->isOccupied()) {
								thereIsRoom = false;
							}
						}

						if (thereIsRoom) {
							Motorcycle* newMotorcycle = new Motorcycle();
							vector<Place*> initPos;
							wesBound.getLane()[0]->setVehicle(newMotorcycle);
							initPos.push_back(wesBound.getLane()[0]);
							newMotorcycle->setPlaces(initPos);
							wesQueue.push(newMotorcycle);
						}
						break;
					}
				}
			}
		}
		
		// Tick the clock of the light
		light.tick();

		// Print the intersection
		print_traffic(lanes);

		//Sleep(150);
		z++;
		// Prompt user for token
		//cout << "Move vehicles? Enter 1 to continue; 0 to exit simulation: ";
		//cin >> token;
	}
}

void print_traffic(vector<Road> const& lanes) {
	// Initilize each lane
	vector<Place*> nor_bound, sou_bound, eas_bound, wes_bound;
	nor_bound = lanes[0].getLane();
	sou_bound = lanes[1].getLane();
	eas_bound = lanes[2].getLane();
	wes_bound = lanes[3].getLane();

	// Print north side of the intersection
	for (int i = 0; i < ROAD_LEN / 2 - 1; i++) {
		for (int j = 0; j < ROAD_LEN; j++) {
			if (j == ROAD_LEN / 2 - 1 || j == ROAD_LEN / 2 + 1 || j == ROAD_LEN / 2 + 3) {
				cout << "|";
			}
			else if (j == 25) {		// Check for car on south bound lane
				Vehicle* v = sou_bound[i]->getVehicle();
				if (sou_bound[i]->isOccupied())
					// Utilize polymorphism to print out the existing vehicle
					v->printVehicle();
				else
					cout << " ";
			}
			else if (j == 27) {		// Check for car on north bound lane
				Vehicle* v = nor_bound[ROAD_LEN - 1 - i]->getVehicle();
				if (nor_bound[ROAD_LEN - 1 - i]->isOccupied())	// Start printing out vehicles at the end of the road
					v->printVehicle();
				else
					cout << " ";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	

	// Print east-west lanes
	for (int i = 0; i < 5; i++) {
		if (i == 0 || i == 4) {
			for (int j = 0; j < ROAD_LEN + 3; j++) {
				if (j == 24 || j == 28) {
					cout << "X";
				}
				else if (j > 24 && j < 28) {
					cout << " ";
				}
				else {
					cout << "-";
				}
			}
		}
		else if (i == 1) {		// Print west bound lane
			Vehicle* v;
			// Print west side of lane
			for (int j = ROAD_LEN - 1; j > ROAD_LEN / 2 ; j--) {
				v = wes_bound[j]->getVehicle();
				if (wes_bound[j]->isOccupied())
					v->printVehicle();
				else
					cout << " ";
			}
			
			// Print intersection segment of the lane
			cout << " ";
			if (wes_bound[ROAD_LEN / 2]->isOccupied())
				wes_bound[ROAD_LEN / 2]->getVehicle()->printVehicle();
			else if (sou_bound[ROAD_LEN / 2 - 1]->isOccupied())					// Top left of intersection is shared between west and south lane
				sou_bound[ROAD_LEN / 2 - 1]->getVehicle()->printVehicle();
			else
				cout << ".";
			cout << " ";
			if (wes_bound[ROAD_LEN / 2 - 1]->isOccupied())
				wes_bound[ROAD_LEN / 2 - 1]->getVehicle()->printVehicle();
			else if (nor_bound[ROAD_LEN / 2]->isOccupied())				// Top right of intersection is shared between west and north lane
				nor_bound[ROAD_LEN / 2]->getVehicle()->printVehicle();
			else
				cout << ".";
			cout << " ";

			// Print east side of lane
			for (int j = ROAD_LEN / 2 - 2; j >= 0; j--) {
				v = wes_bound[j]->getVehicle();
				if (wes_bound[j]->isOccupied())
					v->printVehicle();
				else
					cout << " ";
			}
		}
		else if (i == 2) {	// Print middle of east-west road
			for (int j = 0; j < ROAD_LEN + 3; j++) {
				if (j > 23 && j < 29) {
					cout << " ";
				}
				else {
					cout << "-";
				}
			}
		}
		else if (i == 3) {		// Check for car on east bound lane
			Vehicle* v;
			// Print east side of lane
			for (int j = 0; j < ROAD_LEN / 2 - 1; j++) {
				v = eas_bound[j]->getVehicle();
				if (eas_bound[j]->isOccupied())
					v->printVehicle();
				else
					cout << " ";
			}

			// Print intersection segment of the lane
			cout << " ";
			if (eas_bound[ROAD_LEN / 2 - 1]->isOccupied())
				eas_bound[ROAD_LEN / 2 - 1]->getVehicle()->printVehicle();
			else if (sou_bound[ROAD_LEN / 2]->isOccupied())				// Bot left of intersection is shared between east and south lane
				sou_bound[ROAD_LEN / 2]->getVehicle()->printVehicle();
			else
				cout << ".";
			cout << " ";
			if (eas_bound[ROAD_LEN / 2]->isOccupied())
				eas_bound[ROAD_LEN / 2]->getVehicle()->printVehicle();
			else if (nor_bound[ROAD_LEN / 2 - 1]->isOccupied())					// Bot right of intersetion is shared between east and north lane
				nor_bound[ROAD_LEN / 2 - 1]->getVehicle()->printVehicle();
			else
				cout << ".";
			cout << " ";

			// Print east side of lane
			for (int j = ROAD_LEN / 2 + 1; j < ROAD_LEN; j++) {
				v = eas_bound[j]->getVehicle();
				if (eas_bound[j]->isOccupied())
					v->printVehicle();
				else
					cout << " ";
			}
		}
		cout << endl;
	}

	// Print south side of the intersection
	for (int i = ROAD_LEN / 2 + 1; i < ROAD_LEN; i++) {
		for (int j = 0; j < ROAD_LEN; j++) {
			if (j == ROAD_LEN / 2 - 1 || j == ROAD_LEN / 2 + 1 || j == ROAD_LEN / 2 + 3) {
				cout << "|";
			}
			else if (j == 25) {		// Check for car on south bound lane
				Vehicle* v = sou_bound[i]->getVehicle();
				if (sou_bound[i]->isOccupied())
					// Utilize polymorphism to print out the existing vehicle
					v->printVehicle();
				else
					cout << " ";
			}
			else if (j == 27) {		// Check for car on north bound lane
				Vehicle* v = nor_bound[ROAD_LEN - 1 - i]->getVehicle();
				if (nor_bound[ROAD_LEN - 1 - i]->isOccupied())	// Start printing out vehicles at the end of the road
					v->printVehicle();
				else
					cout << " ";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}
