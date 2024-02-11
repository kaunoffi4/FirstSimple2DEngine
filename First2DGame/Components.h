#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CTransform
{
	
public:
	Vec2 position = { 0.0, 0.0 };
	Vec2 velocity = { 0.0, 0.0 };
	float angle = 0;
	CTransform(const Vec2& pos, const Vec2& vel, float angle) 
		: position(pos), velocity(vel), angle(angle) {}
};

class CShape
{
public:
	sf::CircleShape circle;
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollision
{
public:
	float radius = 0;
	CCollision(float r)
		: radius(r) {}
};

class CScore
{
public:
	int score = 0;
	CScore(int s)
		: score(s) {}
};

class CLifeSpan
{
public:
	int remaining = 0;
	int total = 0;
	CLifeSpan(int total)
		: remaining(total), total(total) {}

};

class CInput
{
public:
	bool up =		false;
	bool left =		false;
	bool right =	false;
	bool down =		false;
	bool shoot =	false;

	CInput() {}
};