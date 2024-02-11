#include "Assets.h"
#include <fstream>
#include <iostream>

sf::Texture& Assets::getTexture(const std::string& name)
{
	return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
	return m_animations[name];
}

sf::Sound& Assets::getSound(const std::string& name)
{
	// TODO: вставьте здесь оператор return
}

sf::Font& Assets::getFont(const std::string& name)
{
	return m_fonts[name];
}

Assets::Assets()
{
}

void Assets::loadFromFile(const std::string& file)
{
	std::string line;
	std::ifstream myfile(file);
	for (std::string type; myfile.is_open() && !myfile.eof(); myfile >> type)
	{
		
		if (type == "Font")
		{
			std::string name, path;
			myfile >> name >> path;
			addFont(name, path);

		}
		else if (type == "Texture")
		{
			std::string name, path;
			int x, y, w, h;
			myfile >> name >> path >> x >> y >> w >> h;
			addTexture(name, path, x, y, w, h);
		}
		else if (type == "Animation")
		{
			std::string name, textureName;
			int frameCount, speed;
			myfile >> name >> textureName >> frameCount >> speed;
			Animation animation(name, getTexture(textureName), frameCount, speed);
			addAnimation(name, animation);

		}
	}
}

void Assets::addTexture(const std::string& name, const std::string& path, int x, int y, int w, int h)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path, sf::IntRect(x, y, w, h)))
	{
		//error
		return;
	}
	m_textures[name] = texture;
}

void Assets::addAnimation(const std::string& name, Animation& animation)
{
	m_animations[name] = animation;
}

void Assets::addSound(const std::string& name, const std::string& path)
{
}

void Assets::addFont(const std::string& name, const std::string& path)
{
	sf::Font font;
	if (!font.loadFromFile(path))
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		m_fonts[name] = font;
	}
	
}
