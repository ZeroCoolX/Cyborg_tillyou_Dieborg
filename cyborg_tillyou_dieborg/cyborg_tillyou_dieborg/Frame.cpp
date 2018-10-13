#include "Frame.h"

void Frame::draw(SDL_Texture* spriteSheet, float x, float y)
{
	SDL_Rect destination; // Where we want to draw this frame
	// set position
	destination.x = x - m_offset.x;
	destination.y = y - m_offset.y;
	// set dimensions
	destination.w = m_clip.w;
	destination.h = m_clip.h;

	render_texture(spriteSheet, Globals::renderer, destination, &m_clip);
}

void Frame::load_frame(ifstream & file, list<DataGroupType>& groupTypes)
{
	GroupBuilder::build_groups(groupTypes, m_frameData);

	string buffer;
	// frame: did data saying this is a frame
	getline(file, buffer);
	
	// clip: 
	getline(file, buffer);
	stringstream ss;
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> m_clip.x >> m_clip.y >> m_clip.w >> m_clip.h;

	// offset:
	getline(file, buffer);
	ss.clear();
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> m_offset.x >> m_offset.y;

	// duration:
	getline(file, buffer);
	ss.clear();
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> m_duration;

	// index:
	getline(file, buffer);
	ss.clear();
	buffer = Globals::clip_off_data_header(buffer);
	ss << buffer;
	ss >> m_frameNumber;

	GroupBuilder::load_groups(file, m_frameData);
}
