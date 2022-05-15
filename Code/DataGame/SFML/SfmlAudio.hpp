#ifndef SFMLAUDIO_H
#define SFMLAUDIO_H
#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

class SfmlAudio
{
private:
public:
	SfmlAudio();
	SfmlAudio(std::string scr);
	~SfmlAudio();

	sf::SoundBuffer buffer;
	sf::Sound sound;
};
#endif