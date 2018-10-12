#ifndef GROUPSTRING_H
#define GROUPSTRING_H

#include "Group.h"

class GroupString : public Group {
public:
	list<string> data;

	GroupString(DataGroupType type) {
		this->type = type;
	}

	int number_of_data_in_group() {
		return data.size();
	}

	void add_to_group(string str) {
		if (str[0] == ' ') {
			str.erase(0, 1);
		}
		data.push_back(str);
	}

	void draw() {
		// TODO
	}
};

#endif // !GROUPSTRING_H

