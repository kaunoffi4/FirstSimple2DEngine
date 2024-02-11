#include "Physics.h"
#include "Components.h"

Physics::Physics()
{

}

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
	// TODO: return the overlap rectangle size of the bounding boxes of entity a and b

	//if (a->hasComponent<CTransform>() && a->hasComponent<CBoundingBox>());	

	Vec2 delta = { std::abs(a->getComponent<CTransform>().pos.x - b->getComponent<CTransform>().pos.x)
		, abs(a->getComponent<CTransform>().pos.y - b->getComponent<CTransform>().pos.y)};

	float ox = a->getComponent<CBoundingBox>().halfSize.x + b->getComponent<CBoundingBox>().halfSize.x - delta.x;
	float oy = a->getComponent<CBoundingBox>().halfSize.y + b->getComponent<CBoundingBox>().halfSize.y - delta.y;

	return Vec2(ox, oy);
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
	Vec2 delta = { std::abs(a->getComponent<CTransform>().prevPos.x - b->getComponent<CTransform>().prevPos.x)
		, abs(a->getComponent<CTransform>().prevPos.y - b->getComponent<CTransform>().prevPos.y) };

	float ox = a->getComponent<CBoundingBox>().halfSize.x + b->getComponent<CBoundingBox>().halfSize.x - delta.x;
	float oy = a->getComponent<CBoundingBox>().halfSize.y + b->getComponent<CBoundingBox>().halfSize.y - delta.y;

	return Vec2(ox, oy);
}


