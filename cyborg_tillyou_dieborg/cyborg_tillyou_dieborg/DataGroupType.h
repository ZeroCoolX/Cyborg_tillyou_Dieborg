#ifndef DATAGROUPTYPE_H
#define DATAGROUPTYPE_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

// Frame data is all about the data. These types help to describe what types of data are in a group
class DataGroupType {
public:
	// STATIC DATA TYPES
	static const int DATATYPE_STRING = 0, DATATYPE_POSITION = 1, DATATYPE_BOX = 2, DATATYPE_NUMBER = 3;

	string m_groupName; // e.g hitBoxes
	int m_dataType; // What do we expect to see here: stirng, position, rectangle region, rotation, ect
	bool m_singleItem; // Can this datagroup only have 1 item inside (usually false, but you never know)

	// Saving and loading these for RuleSets(RS)
	static void save_rs_data_group_type(ofstream& file, DataGroupType dataGroupType);
	static DataGroupType load_rs_data_group_type(ifstream& file);
};

#endif // !DATAGROUPTYPE_H
