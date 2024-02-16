#pragma once

#include "Scene.h"
#include <map>
#include <memory>

#include "EntityManager.h"


const float limit = 0.25;
static float jumpTime = 0;

class Scene_Play : public Scene
{
	struct PlayerConfig
	{
		float GX, GY, CW, CH, SX, SY, SM, G;
		std::string WEAPON;
	};

protected:

	std::shared_ptr<Entity>	m_player;
	std::string				m_levelPath;
	PlayerConfig			m_playerConfig;
	bool					m_drawTextures = true;
	bool					m_drawCollision = false;
	bool					m_drawGrid = false;
	const Vec2				m_gridSize = { 32, 32 };
	sf::Text				m_gridText;

	void init(const std::string& levelPath);

	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	void update();

	void loadLevel(const std::string& filename);
	void spawnPlayer();
	void spawnBullet(std::shared_ptr<Entity> entity);

	void sMovement();
	void sLifeSpan();
	void sCollision();
	void sDoAction(const Action& action);
	void sAnimation();
	void sRender();
	void sEnemySpawner();

	void onEnd();

public:

	Scene_Play(GameEngine* gameEngine, const std::string& levelPath);

	//not the end
};