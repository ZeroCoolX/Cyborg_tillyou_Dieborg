#include "Animation.h"

Animation::Animation(string name):name(name){}

int Animation::get_next_frame_number(int frameNumber)
{
	if (frameNumber + 1 < frames.size()) {
		return frameNumber + 1;
	}
	return 0;
}

Frame* Animation::get_next_frame(Frame* currentFrame)
{
	return get_frame(get_next_frame_number(currentFrame->frameNumber));
}

int Animation::get_end_frame_number()
{
	return frames.size() - 1;
}

Frame* Animation::get_frame(int frameNumber)
{
	if (frames.size() == 0) {
		return NULL;
	}
	list<Frame>::iterator frameIterator = frames.begin();
	
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
