#include "EntityManager.h"
#include <iostream>

void EntityManager::removeDeadEntities(EntityVec& vec)
{

	auto is_dead = [](auto const& e)  {return !(e->isActive()); };
	
	vec.erase(std::remove_if(vec.begin(), vec.end(), is_dead), vec.end());
}

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	for (auto e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
	}

	m_entitiesToAdd.clear();

	removeDeadEntities(m_entities);

	for (auto& entityMap : m_entityMap)
	{
		removeDeadEntities(entityMap.second);
	}

	
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(e);

	return e;
}

const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

const EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}
