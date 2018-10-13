#include "Animation.h"

Animation::Animation(string name):m_name(name){}

int Animation::get_next_frame_number(int frameNumber)
{
	if (frameNumber + 1 < m_frames.size()) {
		return frameNumber + 1;
	}
	return 0;
}

Frame* Animation::get_next_frame(Frame* currentFrame)
{
	return get_frame(get_next_frame_number(currentFrame->m_frameNumber));
}

int Animation::get_end_frame_number()
{
	return m_frames.size() - 1;
}

Frame* Animation::get_frame(int frameNumber)
{
	if (m_frames.size() == 0) {
		return NULL;
	}
	list<Frame>::iterator frameIterator = m_frames.begin();
	
	int counter = 0;
	for (counter = 0; counter < frameNumber && counter < get_end_frame_number(); ++counter) {
		++frameIterator; // Make iterator point to the next frame in the list
	}
	// Memory address to the frame in the slot we're pointing to
	Frame* frame = &(*frameIterator);
		// *frameIterator = gets frame at the position in the list (de-referencing)
		// & = mem address of frame (referencing)
	return frame;
}

void Animation::load_animation(ifstream& file, list<DataGroupType>& groupTypes)
{
	getline(file, m_name);
	string buffer;

	// frames:
	getline(file, buffer);
	stringstream ss;
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	int numberOfFrames;
	ss >> numberOfFrames;
	for (int i = 0; i < numberOfFrames; ++i) {
		Frame newFrame;
		newFrame.load_frame(file, groupTypes);
		m_frames.push_back(newFrame);
	}
}
