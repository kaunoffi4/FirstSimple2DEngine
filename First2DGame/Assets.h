#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Animation.h"

class Assets
{

	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, Animation> m_animations;
	std::map<std::string, sf::Sound> m_sounds;
	std::map<std::string, sf::Font> m_fonts;

public:
		
	Assets();

	void loadFromFile(const std::string& file);

	void addTexture(const std::string& name, const std::string& path, int x, int y, int w, int h);
	void addAnimation(const std::string& name, Animation& animation);
	void addSound(const std::string& name, const std::string& path);
	void addFont(const std::string& name, const std::string& path);

	sf::Texture& getTexture(const std::string& name);
	Animation& getAnimation(const std::string& name);
	sf::Sound& getSound(const std::string& name);
	sf::Font& getFont(const std::string& name);

};