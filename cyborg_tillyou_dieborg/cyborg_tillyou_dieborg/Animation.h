#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"

using namespace std;

class Animation {
public:
	string m_name;
	list<Frame> m_frames;

	Animation(string name = "");

	int get_next_frame_number(int frameNumber);
	Frame* get_next_frame(Frame* currentFrame);
	int get_end_frame_number();
	Frame* get_frame(int frameNumber);
	void load_animation(ifstream& file, list<DataGroupType>& groupTypes);
};

#endif // !ANIMATION_H
