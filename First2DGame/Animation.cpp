#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(const std::string& name, const sf::Texture& t)
	: Animation(name, t, 1, 1)
{
}

Animation::Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed)
	: m_name(name)
	, m_sprite(t)
	, m_currentFrame(0)
	, m_frameCount(frameCount)
	, m_speed(speed)
{
	m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));  // probably wrong
	//m_sprite.setScale(sf::Vector2<float>(2, 2));
	m_size *= 2.0f;
}

// updates the animation to show the next frame, depending on its speed
// animation loops when it reaches the end
void Animation::update()
{
	// add the speed variable to the current frame
	m_currentFrame++;

	// TODO:	1) calculate the correct frame of animation to play based on currentFrame and speed
	//			2) set the texture rectangle properly (see constructor for sample)

	m_size /= 2.0f;

	int animFrame = (m_currentFrame / m_speed) % m_frameCount;
	m_sprite.setTextureRect(sf::IntRect(animFrame * m_size.x, 0, m_size.x, m_size.y));

	m_size *= 2.0f;
}

const Vec2& Animation::getSize() const
{
	return m_size;
}

sf::Sprite& Animation::getSprite()
{
	return m_sprite;
}

const std::string& Animation::getName() const
{
	return m_name;
}

bool Animation::hasEnded() const
{

	// TODO: detect when animation has ended (last frame was played) and return true

	return false;
}
