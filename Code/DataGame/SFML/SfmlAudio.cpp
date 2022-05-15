#include "SfmlAudio.hpp"  
	
SfmlAudio::SfmlAudio()
{
	
}

SfmlAudio::SfmlAudio(std::string scr)
{
     buffer.loadFromFile(scr);
     sound.setBuffer(buffer);
}
	
SfmlAudio::~SfmlAudio()
{
	
}
