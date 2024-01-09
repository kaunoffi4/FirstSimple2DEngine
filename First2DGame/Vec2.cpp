#include "Vec2.h"

Vec2::Vec2()
{
}

Vec2::Vec2(float xin, float yin)
{
	x = xin;
	y = yin;
}

bool Vec2::operator == (const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

Vec2 Vec2::operator/(const float scalar)
{
	return Vec2(x/scalar, y/scalar);
}

Vec2 Vec2::operator*(const float scalar)
{
	return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator- (const Vec2& rhs)
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs)
{
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/(const Vec2& rhs)
{
	return Vec2(x / rhs.x, y / rhs.y);
}

void Vec2::operator /= (const float scalar)
{
	x = x / scalar; 
	y = y / scalar;
}

void Vec2::operator*= (const float scalar)
{
	x = x * scalar;
	y = y * scalar;
}
