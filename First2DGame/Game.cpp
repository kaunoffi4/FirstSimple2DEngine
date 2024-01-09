#include "Game.h"

#include <iostream>
#include <fstream>
#include <cmath>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);

	fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG
		>> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;


	fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT
		>> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;

	fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG
		>> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;

	m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
	m_window.setFramerateLimit(60);

	spawnPlayer();
}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}

void Game::sMovement()
{


	// player part
	m_player->CTransform->velocity = { 0, 0 };

	if (m_player->CInput->up)
	{
		if (m_player->CTransform->position.y - m_playerConfig.SR <= 0)
		{
			m_player->CTransform->velocity.y = 0;
		}
		else
			m_player->CTransform->velocity.y = -m_playerConfig.S;
	}

	if (m_player->CInput->down)
	{
		if (m_player->CTransform->position.y + m_playerConfig.SR >= m_window.getSize().y)
		{
			m_player->CTransform->velocity.y = 0;
		}
		else
			m_player->CTransform->velocity.y = m_playerConfig.S;
	}

	if (m_player->CInput->right)
	{
		if (m_player->CTransform->position.x + m_playerConfig.SR >= m_window.getSize().x)
		{
			m_player->CTransform->velocity.x = 0;
		}
		else
			m_player->CTransform->velocity.x = m_playerConfig.S;
	}

	if (m_player->CInput->left)
	{
		if (m_player->CTransform->position.x - m_playerConfig.SR <= 0)
		{
			m_player->CTransform->velocity.x = 0;
		}
		else
			m_player->CTransform->velocity.x = -m_playerConfig.S;
	}

	m_player->CTransform->position.x += m_player->CTransform->velocity.x;
	m_player->CTransform->position.y += m_player->CTransform->velocity.y;


	// entity part

	for (auto e : m_entities.getEntities())
	{
		e->CTransform->position.x += e->CTransform->velocity.x;
		e->CTransform->position.y += e->CTransform->velocity.y;
	}


}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->CInput->up = true;
				break;
			case sf::Keyboard::S:
				m_player->CInput->down = true;
				break;
			case sf::Keyboard::A:
				m_player->CInput->left = true;
				break;
			case sf::Keyboard::D:
				m_player->CInput->right = true;
				break;
			case sf::Keyboard::F9:
				m_paused = true;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->CInput->up = false;
				break;
			case sf::Keyboard::S:
				m_player->CInput->down = false;
				break;
			case sf::Keyboard::A:
				m_player->CInput->left = false;
				break;
			case sf::Keyboard::D:
				m_player->CInput->right = false;
				break;
			case sf::Keyboard::F9:
				m_paused = false;
				break;
			default: break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//std::cout << "LMB Clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				//call spawnBullet here
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "RMB Clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
				//call specialWeapon here
			}

		}
	}
}

void Game::sLifeSpan()
{

	for (auto b : m_entities.getEntities("bullet"))
	{

		if (--b->CLifeSpan->remaining == 0)
			b->m_active = false;

		sf::Color color = b->CShape->circle.getFillColor();  
		color.a = 255 * 0.01 * b->CLifeSpan->remaining;  
		b->CShape->circle.setFillColor(color);  

		color = b->CShape->circle.getOutlineColor();  
		color.a = 255 * 0.01 * b->CLifeSpan->remaining; 
		b->CShape->circle.setOutlineColor(color); 
	}

	for (auto e : m_entities.getEntities("smallEnemy"))
	{
		if (--e->CLifeSpan->remaining == 0)
			e->m_active = false;

		sf::Color color = e->CShape->circle.getFillColor();  
		color.a = 255 * 0.01 * e->CLifeSpan->remaining;  
		e->CShape->circle.setFillColor(color);  

		color = e->CShape->circle.getOutlineColor();  
		color.a = 255 * 0.01 * e->CLifeSpan->remaining;  
		e->CShape->circle.setOutlineColor(color);  
	}
}

void Game::sRender()
{
	m_window.clear();

	//std::cout << m_entities.getEntities().size() << '\n';
	for (auto e : m_entities.getEntities())
	{
		e->CShape->circle.setPosition(e->CTransform->position.x, e->CTransform->position.y);

		e->CTransform->angle += 1.0f;
		e->CShape->circle.setRotation(e->CTransform->angle);
		m_window.draw(e->CShape->circle);
	}

	m_window.display();


}

void Game::sEnemySpawner()
{

	spawnEnemy();
	sLifeSpan();

}

void Game::sCollision()
{
	for (auto e : m_entities.getEntities("enemy"))
	{
		if (e->CTransform->position.x <= 0 + m_enemyConfig.CR || e->CTransform->position.x >= m_window.getSize().x - m_enemyConfig.CR)
		{
			e->CTransform->velocity.x *= -1;
		}
		if (e->CTransform->position.y <= 0 + m_enemyConfig.CR || e->CTransform->position.y >= m_window.getSize().y - m_enemyConfig.CR)
		{
			e->CTransform->velocity.y *= -1;
		}

		if ((pow(m_enemyConfig.CR + m_playerConfig.CR, 2)) >= pow(e->CTransform->position.x - getPlayerPosition().x, 2) +
			pow(e->CTransform->position.y - getPlayerPosition().y, 2))
		{
			m_running = false;
		}
		for (auto b : m_entities.getEntities("bullet"))
		{

			if ((pow(m_enemyConfig.CR + m_bulletConfig.CR, 2)) >= pow(e->CTransform->position.x - b->CTransform->position.x, 2) +
				pow(e->CTransform->position.y - b->CTransform->position.y, 2))
			{
				b->m_active = false;
				e->m_active = false;
				std::cout << "Collision\n";
				spawnSmallEnemies(e);
			}
		}
	}
}

void Game::spawnPlayer()
{
	auto p = m_entities.addEntity("player");
	p->CTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(0.0f, 0.0f), 0.0f);
	p->CShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR,
		m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
	p->CInput = std::make_shared<CInput>();

	m_player = p;
}

void Game::spawnEnemy()
{

	if (m_currentFrame - m_lastEnemySpawnTime < m_enemyConfig.SI)
		return;
	auto e = m_entities.addEntity("enemy");

	float ex = rand() % (m_window.getSize().x - (m_enemyConfig.SR << 1)) + m_enemyConfig.SR;
	float ey = rand() % (m_window.getSize().y - (m_enemyConfig.SR << 1)) + m_enemyConfig.SR;

	
	int r, g, b;
	r = rand() % 255, g = rand() % 255, b = rand() % 255;
	float speed = rand() % (int)(m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1) + m_enemyConfig.SMIN;

	float speedX = speed * (rand() % 2 == 1 ? -1 : 1);
	float speedY = speed * (rand() % 2 == 1 ? -1 : 1);

	e->CTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(speedX, speedY), 0.0f);
	e->CShape = std::make_shared<CShape>(m_enemyConfig.SR, (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN)) + m_enemyConfig.VMIN, sf::Color(r,g,b), sf::Color(m_enemyConfig.OR,
		m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);


	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
	int sides = entity->CShape->circle.getPointCount();
	float angle = 360.0f / sides;
	for (int i = 0; i < sides; ++i) {
		float x = abs(entity->CTransform->velocity.x) * std::cos(i * angle * 3.14159f / 180.0f);
		float y = abs(entity->CTransform->velocity.x) * std::sin(i * angle * 3.14159f / 180.0f);
		auto p = m_entities.addEntity("smallEnemy");
		p->CTransform = std::make_shared<CTransform>(entity->CTransform->position, Vec2(x, y), 0);
		p->CShape = entity->CShape;
		p->CShape->circle.setRadius(8);
		p->CLifeSpan = std::make_shared<CLifeSpan>(90);
	}
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	auto b = m_entities.addEntity("bullet");

	Vec2 mousePosDublicate = mousePos;
	Vec2 vec = { mousePosDublicate - entity->CTransform->position };
	float length = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	vec /= length;
	vec *= m_bulletConfig.S;
	
	b->CTransform = std::make_shared<CTransform>(Vec2(entity->CTransform->position.x, entity->CTransform->position.y), vec, 0);
	b->CShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
		sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
	b->CLifeSpan = std::make_shared<CLifeSpan>(m_bulletConfig.L);


}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
}

Vec2 Game::getPlayerPosition()
{
	return Vec2(m_player->CTransform->position.x, m_player->CTransform->position.y);
}


void Game::run()
{
	while (m_running)
	{

		if (!m_paused)
		{
			m_entities.update();
			sEnemySpawner();
			sMovement();
			sCollision();
			sUserInput();
		}
		sRender();

		m_currentFrame++;
	}
}
