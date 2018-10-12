#include "GroupBuilder.h"

const bool GroupBuilder::SAVED_IN_GROUPS = false;

Group* GroupBuilder::build_group(DataGroupType dataType)
{
	Group* group = NULL;

	if (dataType.dataType == DataGroupType::DATATYPE_NUMBER)
	{
		group = new GroupNumber(dataType);
	}
	else if (dataType.dataType == DataGroupType::DATATYPE_POSITION)
	{
		group = new GroupPosition(dataType);
	}
	else if (dataType.dataType == DataGroupType::DATATYPE_BOX)
	{
		group = new GroupBox(dataType);
	}
	else {
		group = new GroupString(dataType);
	}

	return group;
}

void GroupBuilder::build_groups(list<DataGroupType> groupTypes, list<Group*>& groups)
{
	for (list<DataGroupType>::iterator dgt = groupTypes.begin(); dgt != groupTypes.end(); dgt++)
	{
		Group* group = build_group((*dgt));
		groups.push_back(group);
	}
}

Group* GroupBuilder::add_group_string_to_group(string name, list<Group*>& groups)
{
	DataGroupType dgt;
	dgt.dataType = DataGroupType::DATATYPE_STRING;
	dgt.groupName = name;
	dgt.singleItem = false;
	Group* group = new GroupString(dgt);
	groups.push_back(group); //ok, we just added some random group on the fly for this frame only. cool, I hope
	return group;
}

void GroupBuilder::load_groups(ifstream& file, list<Group*>& groups)
{
	// Read each group in:
	while (!file.eof()) {
		// Fist get the next line out of the file
		int positionBeforeRead = file.tellg();
		string line;
		getline(file, line);
		if (line.empty() || line == "") {
			break;
		}
		if (SAVED_IN_GROUPS) {
			// Find the colon
			int pos = line.find(":", 0);
			if (pos == -1) {
				file.seekg(positionBeforeRead);
				break; // Must actually be reading something else, like the next animation or something.
			}
			Group* group = find_group_by_name(line.substr(0, pos), groups);
			if (group == NULL) {
				// Cannot find the group but lets not lose the data
				group = add_group_string_to_group(line.substr(0, pos), groups);
			}
			// Ok get the rest of the string and work out how many of these we have to build
			string numStr = line.substr(pos + 1, line.length() - pos + 2);
			stringstream ss;
			ss << numStr << endl;
			int num;
			ss >> num;
			// Finally can read in all the data
			for (int i = 0; i < num; ++i) {
				if (!file.good()) {
					break;
				}
				getline(file, line);
				group->add_to_group(line);
			}
		}
		else {
			// Dealing with 1 item at a time, regardless of in a group or not
			// Find the colon
			int pos = line.find(":", 0);
			if (pos == -1) {
				file.seekg(positionBeforeRead);
				break; // Must actually be reading something else, like the next animation or something.
			}
			cout << "sub:" << line.substr(0, pos) << endl;
			Group* group = find_group_by_name(line.substr(0, pos), groups);
			if (group == NULL) {
				// Cannot find the group but lets not lose the data
				group = add_group_string_to_group(line.substr(0, pos), groups);
			}
			//line = Globals::clip_off_data_header(line);//get rid of the 'groupName: '
			group->add_to_group(line);
		}
	}
}

Group* GroupBuilder::find_group_by_name(string name, list<Group*>& groups)
{
	for (list<Group*>::iterator group = groups.begin(); group != groups.end(); group++)
	{
		if (name == (*group)->type.groupName)
			return (*group);
	}

	return NULL;
}
