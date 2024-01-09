#pragma once

#include "Components.h"
#include <string>
#include <iostream>


class Entity
{
	friend class EntityManager;

	size_t m_id = 0;
	std::string m_tag = "default";

	Entity(const size_t id, const std::string& tag)
		: m_id(id), m_tag(tag) {}


public:
	bool m_active = true;
	std::shared_ptr<CTransform> CTransform;
	std::shared_ptr<CShape> CShape;
	std::shared_ptr<CCollision> CCollision;
	std::shared_ptr<CScore> CScore;
	std::shared_ptr<CLifeSpan> CLifeSpan;
	std::shared_ptr<CInput> CInput;

	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();
};