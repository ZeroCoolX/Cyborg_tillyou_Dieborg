#ifndef GROUPPOS_H
#define GROUPPOS_H

#include "Group.h"

class GroupPosition : public Group {
public:
	list<SDL_Point> m_data;

	GroupPosition(DataGroupType type) {
		m_type = type;
	}

	int number_of_data_in_group() {
		return m_data.size();
	}

	void add_to_group(string str) {
		stringstream ss;
		ss << str;
		SDL_Point point;
		ss >> point.x >> point.y;
		m_data.push_back(point);
	}

	void draw() {
		// TODO
	}
};

#endif // !GROUPPOS_H
