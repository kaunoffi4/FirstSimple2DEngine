#include "Scene.h"
#include "GameEngine.h"

void Scene::doAction(const Action& action)
{
	sDoAction(action);
}

void Scene::simulate(const size_t frames)
{
}

void Scene::registerAction(int inputKey, const std::string& actionName)
{
	m_actionMap[inputKey] = actionName;
}

size_t Scene::width() const
{
	//return size_t(m_game->window().getSize().x);
	return size_t();
}

size_t Scene::height() const
{
	//return size_t(m_game->window().getSize().y);
	return size_t();
}

size_t Scene::currentFrame() const
{
	return size_t();
}

bool Scene::hasEnded() const
{
	return false;
}

const ActionMap& Scene::getActionMap() const
{
	return m_actionMap;
}

void Scene::drawLine(const sf::Vector2<float>& point1, const sf::Vector2<float>& point2)
{
	sf::Vertex vertices[4];
	sf::Vector2f direction = point2 - point1;
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (2.f / 2.f) * unitPerpendicular;

	vertices[0].position = point1 + offset;
	vertices[1].position = point2 + offset;
	vertices[2].position = point2 - offset;
	vertices[3].position = point1 - offset;

	for (int i = 0; i < 4; ++i)
	{
		vertices[i].color = sf::Color::White;
	}

	m_game->window().draw(vertices, 4, sf::Quads);
}

void Scene::setPaused(bool paused)
{
}

Scene::Scene()
{
}

Scene::Scene(GameEngine* gameEngine)
{
	m_game = gameEngine;
}
