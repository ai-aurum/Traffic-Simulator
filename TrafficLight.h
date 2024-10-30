// TrafficLight.h
#pragma once
class TrafficLight {
private:
	int duration;	// Determines the length of each light cycle
	int yellow;		// Determines the length of a yellow light
	bool flow;	// Determines if north/south(0) or east/west(1) lanes are green or red
	int elapsed = 0;
public:
	// CONSTRUCTORS
	TrafficLight();
	TrafficLight(int duration, int yellow, bool flow);
	TrafficLight(TrafficLight const& og);
	~TrafficLight();

	// ACCESSOR MEMBER FUNCTIONS
	int getDuration() const;
	int getYellow() const;
	bool getFlow() const;
	int getElapsed() const;

	// MODIFICATION MEMBER FUNCTIONS
	void setDuration(int duration);
	void setYellow(int yellow);
	void setFlow(bool flow);
	void switchFlow();
	void tick();	// increments the elapsed time by 1

	// OTHER
	
};