# Traffic Simulator
 
 This program runs a traffic simulation of a 4-way intersection in which each frame represents a tick or a change in time. Vehicles are only able to cross the intersection if their light is green, and cannot cross if the light is yellow or red. Vehicle types include Motorcycle, Car, Truck, and Bus, which all contain their unique lengths, names, and various other data members. 

 The structure of the intersection is composed of Place objects that Vehicles can occupy, and 4 Road objects that are built from a linked list of Place objects that determine the flow of traffic along the direction of the linkage. Queues are utilized to handle traffic priority within a Road, allowing the Vehicle at the front of the queue to first be moved. As one of my final projects in my C++ and Object Oriented Programming Course, it stands as one of my most complex and lengthy projects.
