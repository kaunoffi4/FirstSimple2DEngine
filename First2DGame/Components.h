#pragma once

#include "Animation.h"
#include "Assets.h"
#include "Vec2.h" //try to delete this later



class Component
{
public:
	bool has = false;
};

class CTransform : public Component
{
	
public:
	Vec2 pos = { 0.0, 0.0 };
	Vec2 prevPos = { 0.0, 0.0 };
	Vec2 velocity = { 0.0, 0.0 };
	Vec2 scale = { 1.0, 1.0 };
	float angle = 0;

	CTransform() {}
	CTransform(const Vec2& p)
		: pos(p) {}
	CTransform(const Vec2& pos, const Vec2& vel, const Vec2& sc, float angle) 
		: pos(pos), prevPos(pos), velocity(vel), scale(sc), angle(angle) {}
};

class CShape : public Component
{
public:
	sf::CircleShape circle;
	
	CShape()
	{

	}

	CShape(CShape& other)
	{
		*this = other;
	}
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollision : public Component
{
public:
	float radius = 0;
	CCollision()
	{

	}
	CCollision(float r)
		: radius(r) {}
};

class CScore : public Component
{
public:
	int score = 0;
	CScore()
	{

	}
	CScore(int s)
		: score(s) {}
};

class CLifeSpan : public Component
{
public:
	int remaining = 0;
	int total = 0;
	CLifeSpan() {}
	CLifeSpan(int total)
		: remaining(total), total(total) {}

};

class CInput : public Component
{
public:
	bool up =		false;
	bool left =		false;
	bool right =	false;
	bool down =		false;
	bool shoot =	false;
	bool canShoot = true;
	bool canJump = true;
	CInput() {}
};

class CBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox() {}
	CBoundingBox(const Vec2& s)
		: size(s), halfSize(s.x / 2, s.y / 2) {}
};

class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;
	CAnimation() {}
	CAnimation(const Animation& animation, bool r)
		: animation(animation), repeat(r) {}
};

class CGravity : public Component
{
public:
	float gravity = 0;
	CGravity() {}
	CGravity(float g) : gravity(g) {}
};

class CState : public Component
{
public:
	std::string state = "STANDING";
	CState() {}
	CState(const std::string& s) : state(s) {}
};