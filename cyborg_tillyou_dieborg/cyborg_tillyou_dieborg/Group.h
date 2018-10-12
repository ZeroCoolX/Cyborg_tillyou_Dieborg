#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<list>
#include<SDL.h>
#include "DataGroupType.h"

using namespace std;

#ifndef GROUP_H
#define GROUP_H

// ABSTRACT CLASS
// Groups manage a FramesData class

class Group {
public:
	DataGroupType type; // Decribes its name, type, and other rules
	Group() {
		// Do nothing
	}
	Group(DataGroupType type) {
		this->type = type;
	}
	// How many bitss of data in here
	virtual int number_of_data_in_group() = 0;
	virtual void add_to_group(string str) = 0;

	virtual void draw() = 0;
};

#endif // !GROUP_H
