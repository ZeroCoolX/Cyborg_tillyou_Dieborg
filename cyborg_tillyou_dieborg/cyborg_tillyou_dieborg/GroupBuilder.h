#ifndef GROUPBUILDER_H
#define GROUPBUILDER_H

#include "Globals.h"
#include "Group.h"
#include "GroupBox.h"
#include "GroupPosition.h"
#include "GroupNumber.h"
#include "GroupString.h"

class GroupBuilder {
public:
	/**
	NOTE: This is the only one a user has to set. As it depends on if they have their data output in groups or not
	In groups example:
	hitboxes: 2
	12 12 34 56
	24 45 57 79
	Not In Groups: (DEFAULT CHOICE)
	hitboxes: 12 12 34 56
	hitboxes: 24 45 57 79
	If in doubt, check the fdset and see what happens with the data
	*/
	static const bool SAVED_IN_GROUPS;

	// Builds a Group based on dataType. Default is STRING becayse we may want to ignore some data in a set but still load it
	static Group* build_group(DataGroupType dataType);
	// Builds a set of Groups based on dataGroupTypes list
	static void build_groups(list<DataGroupType> groupTypes, list<Group*>& groups);
	// Add GroupString to groups (build on the fly). Gives back a reference, if you need one
	static Group* add_group_string_to_group(string name, list<Group*>& groups);
	// Loads a group out to a file
	static void load_groups(ifstream& file, list<Group*>& groups);
	// Finds a group based on a name. Can return null
	static Group* find_group_by_name(string name, list<Group*>& groups);
};

#endif // !GROUPBUILDER
