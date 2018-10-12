#ifndef GROUPNUMBER_H
#define GROUPNUMBER_H

#include "Group.h"

class GroupNumber : public Group {
public:
	list<float> data;

	GroupNumber(DataGroupType type) {
		this->type = type;
	}

	int number_of_data_in_group() {
		return data.size();
	}

	void add_to_group(string str) {
		stringstream ss;
		ss << str;
		float r;
		data.push_back(r);
	}

	void draw() {
		// TODO
	}
};

#endif // !GROUPNUMBER_H
