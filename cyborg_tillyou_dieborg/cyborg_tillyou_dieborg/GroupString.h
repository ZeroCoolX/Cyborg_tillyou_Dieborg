#ifndef GROUPSTRING_H
#define GROUPSTRING_H

#include "Group.h"

class GroupString : public Group {
public:
	list<string> m_data;

	GroupString(DataGroupType type) {
		m_type = type;
	}

	int number_of_data_in_group() {
		return m_data.size();
	}

	void add_to_group(string str) {
		if (str[0] == ' ') {
			str.erase(0, 1);
		}
		m_data.push_back(str);
	}

	void draw() {
		// TODO
	}
};

#endif // !GROUPSTRING_H

