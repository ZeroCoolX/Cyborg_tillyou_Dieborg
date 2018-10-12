#ifndef GROUPPOS_H
#define GROUPPOS_H

#include "Group.h"

class GroupPosition : public Group {
public:
	list<SDL_Point> data;

	GroupPosition(DataGroupType type) {
		this->type = type;
	}

	int number_of_data_in_group() {
		return data.size();
	}

	void add_to_group(string str) {
		stringstream ss;
		ss << str;
		SDL_Point point;
		ss >> point.x >> point.y;
		data.push_back(point);
	}

	void draw() {
		// TODO
	}
};

#endif // !GROUPPOS_H
