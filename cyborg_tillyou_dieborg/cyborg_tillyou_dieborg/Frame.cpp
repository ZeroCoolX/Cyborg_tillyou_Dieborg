#include "Frame.h"

void Frame::draw(SDL_Texture* spriteSheet, float x, float y)
{
	SDL_Rect destination; // Where we want to draw this frame
	// set position
	destination.x = x - offset.x;
	destination.y = y - offset.y;
	// set dimensions
	destination.w = clip.w;
	destination.h = clip.h;

	render_texture(spriteSheet, Globals::renderer, destination, &clip);
}

void Frame::load_frame(ifstream & file, list<DataGroupType>& groupTypes)
{
	GroupBuilder::build_groups(groupTypes, frameData);

	string buffer;
	// frame: did data saying this is a frame
	getline(file, buffer);
	
	// clip: 
	getline(file, buffer);
	stringstream ss;
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> clip.x >> clip.y >> clip.w >> clip.h;

	// offset:
	getline(file, buffer);
	ss.clear();
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> offset.x >> offset.y;

	// duration:
	getline(file, buffer);
	ss.clear();
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> duration;

	// index:
	getline(file, buffer);
	ss.clear();
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> frameNumber;

	GroupBuilder::load_groups(file, frameData);
}
