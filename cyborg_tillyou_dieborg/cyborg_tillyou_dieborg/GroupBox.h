#ifndef GROUPBOX_H
#define GROUPBOX_H

#include "Group.h"

class GroupBox : public Group {
public:
	list<SDL_Rect> m_data;

	GroupBox(DataGroupType type) {
		m_type = type;
	}

	int number_of_data_in_group() {
		return m_data.size();
	}

	void add_to_group(string str) {
		stringstream ss;
		ss << str;
		SDL_Rect box;
		ss >> box.x >> box.y >> box.w >> box.h;
		m_data.push_back(box);
	}

	void draw() {
		// TODO
	}
};

#endif // !GROUPBOX_H
