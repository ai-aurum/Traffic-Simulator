// Place.h
#ifndef PLACE_H
#define PLACE_H

#include <iostream>
#include <vector>
#include <utility>

class Vehicle;

using namespace std;

// Each place represents one patch of asphalt
class Place {
private:
    // DATA MEMBERS
    // Pointers to other Places
    Place* nor;
    Place* sou;
    Place* eas;
    Place* wes;

    // Coordinates
    pair<int, int> loc;

    // Pointer to car
    Vehicle* vpoint;

public:
    // CONSTRUCTORS
    Place();
    Place(pair<int, int> &loc);
    Place(Place const &og);
    ~Place();

    // ACCESSOR MEMBER FUNCTIONS
    Place* getNor() const;
    Place* getSou() const;
    Place* getEas() const;
    Place* getWes() const;
    pair<int, int> getLoc() const;
    Vehicle* getVehicle() const;
    bool isOccupied() const;

    // MODIFICATION MEMBER FUNCTIONS
    void setNor(Place* newNor);
    void setSou(Place* newSou);
    void setWes(Place* newWest);
    void setEas(Place*newEas);
    void setLoc(pair<int, int>& loc);
    void setVehicle(Vehicle* veh);
};

#endif
