#include "Scene_Play.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"

#include <fstream>
#include <iostream>

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine)
	, m_levelPath(levelPath)
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");

	registerAction(sf::Keyboard::W, "JUMP");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Space, "SHOOT");


	//TODO: Register all other gameplay Actions
	
	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_game->assets().getFont("Arial"));

	loadLevel(levelPath);
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	//TODO: This function takes in a grid (x,y) pos and an Entity 
	// Return a Vec2 indicating where the CENTER pos of the entity should be
	// You must use the Entity's Animation size to pos it correctly 
	// The size of the grid width and height is stored in m_gridSize 
	// The bottom-left corner of the Animation should align with the bottom left of the grid cell
	
	int currYPoint = (m_game->window().getSize().y - m_gridSize.y) - (gridY * m_gridSize.y);
	return Vec2((gridX * m_gridSize.x) + (entity->getComponent<CAnimation>().animation.getSize().x / 2)
		, currYPoint + (entity->getComponent<CAnimation>().animation.getSize().y / 2));
}

void Scene_Play::loadLevel(const std::string& filename)
{
	//reset the entity manager every time we load a level 
	m_entityManager = EntityManager();
	
	//TODO: read in the level file and add the appropriate entities
	//		use the PlayerConfig struct m_playerConfig to store player properties
	
	//NOTE: all the code below is sample code which shows you how to set up and use entities with the new syntax, it shoud be removed



	std::ifstream myfile(filename);
	for (std::string type; myfile.is_open() && !myfile.eof();)
	{
		myfile >> type;
		if (type != "Player")
		{
			auto e = m_entityManager.addEntity(type);
			myfile >> type;
			e->addComponent<CAnimation>(m_game->assets().getAnimation(type), true);
			float gridX, gridY;
			myfile >> gridX >> gridY;
			e->addComponent<CTransform>(gridToMidPixel(gridX, gridY, e), Vec2(0, 0), Vec2(2, 2), 0);
			e->addComponent<CBoundingBox>(m_game->assets().getAnimation(type).getSize());
		}
		else
		{
			myfile >> m_playerConfig.GX >> m_playerConfig.GY >> m_playerConfig.CW >> m_playerConfig.CH >> m_playerConfig.SX >> m_playerConfig.SY >> m_playerConfig.SM
				>> m_playerConfig.G >> m_playerConfig.WEAPON;
		}
	}


	std::cout << "X coordinate: " << m_playerConfig.GX << std::endl
		<< "Y coordinate: " << m_playerConfig.GY << std::endl
		<< "Gravity: " << m_playerConfig.G << std::endl
		<< "TWidth: " << m_playerConfig.CW << std::endl
		<< "THeight: " << m_playerConfig.CH << std::endl
		<< "Jump speed: " << m_playerConfig.SY << std::endl
		<< "Run (left/right) speed: " << m_playerConfig.SX << std::endl
		<< "Max speed: " << m_playerConfig.SM << std::endl;

	spawnPlayer();



	//some sample entities
	//auto brick = m_entityManager.addEntity("tile");
	//IMPORTANT: always add the CAnimation component first so that gridToMidPixel can compute correctly
	//brick->addComponent<CAnimation>(m_game->assets().getAnimation("Brick"), true);
	//brick->addComponent<CTransform>(Vec2(96, 480), Vec2(0, 0), Vec2(2, 2), 0);
	//NOTE: you final code should position the entity with the grid x, y position read from the file:

	/*if (brick->getComponent<CAnimation>().animation.getName() == "Brick")
	{
		std::cout << "This could be a good way of identifying if a tile is a brick!\n";
	}*/
	


	//NOTE: THIS IS INCREDIBLY IMPORTANT PLEASE READ THIS EXAMPLE
	//		Components are now returned as reference rather than pointers
	//		if you do not specify a reference variable type, it will COPY the component

	}

void Scene_Play::spawnPlayer()
{
	//here is a sample player entity which you can use to construct other entities
	m_player = m_entityManager.addEntity("Player");
	m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Stand"), true);
	m_player->addComponent<CTransform>(gridToMidPixel(m_playerConfig.GX, m_playerConfig.GY, m_player), Vec2(m_playerConfig.SX, m_playerConfig.SY), Vec2(1.5, 1.5), 0);
	m_player->addComponent<CBoundingBox>(Vec2(m_playerConfig.CW, m_playerConfig.CH));
	m_player->addComponent<CGravity>(m_playerConfig.G);

	//TODO: be sure to add the remaining components to the player 
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
	//TODO: this should spawn a bullet at the given entity, going in the direction the entity is facing

	auto bullet = m_entityManager.addEntity("Bullet");
	bullet->addComponent<CShape>(8, 32, sf::Color(255, 255, 255), sf::Color::White, 1);
	float xVelocity = m_player->getComponent<CAnimation>().animation.getSprite().getScale().x < 0 ? -1 : 1;
	bullet->addComponent<CTransform>(m_player->getComponent<CTransform>().pos, Vec2(xVelocity, 0), Vec2(1, 1), 0);
	bullet->addComponent<CLifeSpan>(240);
}

void Scene_Play::update()
{
	m_entityManager.update();

	//TODO: implement pause functionality

	//sLifeSpan();
	sMovement();
	sCollision();
	sAnimation();

	sRender();
}

void Scene_Play::sMovement()
{
	//TODO: implement player movement / jumping based on its CInput component
	//		implement gravity's effect on the player
	//		implement the maximum player speed in both X and Y directions
	//		NOTE: setting an entity's scale.x to -1/1 will make it face to the left/right


	//player part

	Vec2 playerVelocity(0, m_player->getComponent<CTransform>().velocity.y);


	if (m_player->getComponent<CInput>().up) 
	{

		jumpTime += m_game->getDeltaTime().asMilliseconds();
		if(jumpTime <= limit)
			playerVelocity.y = -m_playerConfig.SY;  // sort out
	}

	if (m_player->getComponent<CInput>().right)
	{
		playerVelocity.x = m_playerConfig.SX;
	}

	if (m_player->getComponent<CInput>().left)
	{
		playerVelocity.x = -m_playerConfig.SX;
	}

	m_player->getComponent<CTransform>().velocity = playerVelocity;



	for (std::shared_ptr<Entity> e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CGravity>())
		{
			e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;   

			if (e->getComponent<CTransform>().velocity.y > m_playerConfig.SM)
			{
				e->getComponent<CTransform>().velocity.y = m_playerConfig.SM;
			}

			//check if the player is moving faster than maxSpeed in any direction
			//set its speed in that direction to the maxSpeed
		}
		e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;
		e->getComponent<CTransform>().pos += e->getComponent<CTransform>().velocity * m_game->getDeltaTime().asMilliseconds(); // sort out
	}
}

void Scene_Play::sLifeSpan()
{
	//TODO: Check lifespan of entities that have them, and destroy them if they go over
}

void Scene_Play::sCollision()
{
	//TODO: implement Physics::GetOverlap() func, use it inside this function
	//TODO: implement bullet / tile collision
	//		destroy the tile if it has a Brick animation
	//TODO: implement player / tile collisions and resolutions 
	//		update the CState component of the player to store whether 
	//		it is currently on the ground or in the air. This will be 
	//		used in the Animation system
	//TODO: check to see if the player has fallen down a hole (y > height())
	//TODO: don't let the player walk off the left side of the map


	if (m_player->getComponent<CTransform>().pos.y - m_player->getComponent<CBoundingBox>().halfSize.y > m_game->window().getSize().y)
	{
		m_player->getComponent<CTransform>().pos = Vec2(gridToMidPixel(m_playerConfig.GX, m_playerConfig.GY, m_player));
		return;
	}

	if (m_player->getComponent<CTransform>().pos.x - m_player->getComponent<CBoundingBox>().halfSize.x <= 0)
	{
		m_player->getComponent<CTransform>().pos.x = m_player->getComponent<CBoundingBox>().halfSize.x + 1;
	}

	Physics p; // may be we could do better
	bool flag = false;
	for (std::shared_ptr<Entity> tile : m_entityManager.getEntities("Tile"))
	{

			Vec2 collision = p.GetOverlap(tile, m_player);
			if (collision.x >= 0 && collision.y >= 0)
			{
				flag = true;

				Vec2 prevCollision = p.GetPreviousOverlap(tile, m_player);


				if (prevCollision.x > 0)
				{
					m_player->getComponent<CTransform>().velocity.y = 0;

					if (m_player->getComponent<CTransform>().prevPos.y <= m_player->getComponent<CTransform>().pos.y)
					{
						m_player->getComponent<CTransform>().pos.y -= collision.y;
						m_player->getComponent<CState>().state = "GROUND";
						m_player->getComponent<CInput>().canJump = true;
					}
					else
					{
						m_player->getComponent<CTransform>().pos.y += collision.y;
						m_player->getComponent<CState>().state = "AIR";
					}
				}

				else if (prevCollision.y > 0)
				{

					if (m_player->getComponent<CTransform>().prevPos.x < m_player->getComponent<CTransform>().pos.x)
					{
						m_player->getComponent<CTransform>().pos.x -= collision.x;
					}
					else
					{
						m_player->getComponent<CTransform>().pos.x += collision.x;
					}
				}
			}
	}
	if (!flag)
	{
		m_player->getComponent<CState>().state = "AIR";
		m_player->getComponent<CInput>().canJump = false;
	}

	for (std::shared_ptr<Entity> tile : m_entityManager.getEntities("Tile"))
	{
		for (std::shared_ptr<Entity> bullet : m_entityManager.getEntities("Bullet"))
		{
			Vec2 collision = p.GetOverlap(tile, bullet);
			if (collision.x >= 0 && collision.y >= 0)
			{
				bullet->m_active = false;
				if (tile->getComponent<CAnimation>().animation.getName() == "Brick")
				{
					tile->m_active = false;
				}
			}
		}
	}

	std::cout << "State: " << m_player->getComponent<CState>().state << std::endl;

	
}

void Scene_Play::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
				  if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
			 else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
			 else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
			 else if (action.name() == "PAUSE") { setPaused(!m_paused); }
			 else if (action.name() == "QUIT") { onEnd(); }
			 else if (action.name() == "JUMP" && m_player->getComponent<CInput>().canJump)
				  { 
					  m_player->getComponent<CInput>().up = true;
					  m_player->getComponent<CInput>().canJump = false;
					  jumpTime = 0;
				  } 
			 else if (action.name() == "RIGHT")
				  {
					  m_player->getComponent<CInput>().right = true;
				  }
			 else if (action.name() == "LEFT")
				  {
					  m_player->getComponent<CInput>().left = true;
				  }
			 else if (action.name() == "SHOOT" && m_player->getComponent<CInput>().canShoot)
				  {
					  m_player->getComponent<CInput>().shoot = true;
					  spawnBullet(m_player);
				  }
	}
	else if (action.type() == "END")
	{
		if (action.name() == "JUMP")
		{
			m_player->getComponent<CInput>().up = false;
		}
		else if (action.name() == "RIGHT")
		{
			m_player->getComponent<CInput>().right = false;
		}
		else if (action.name() == "LEFT")
		{
			m_player->getComponent<CInput>().left = false;
		}
	}
}


void Scene_Play::sAnimation()
{
	//TODO: complete the animation class code first

	//TODO: set the animation of the player based on its CState component
	//TODO: for each entity with an animation, call entity->getComponent<CAnimation>().animation.update()
	//		if the animation is not repeated, and it has ended, destroy the entity

	if (m_player->getComponent<CState>().state == "GROUND")
	{
		if (m_player->getComponent<CTransform>().velocity.x != 0 && m_player->getComponent<CAnimation>().animation.getName() != "Run")
		{
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Run"), true);
		}
		else if (m_player->getComponent<CTransform>().velocity == Vec2(0, 0) && m_player->getComponent<CAnimation>().animation.getName() != "Stand")
		{
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Stand"), true);
		}
	}

	for (std::shared_ptr<Entity> e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CAnimation>())
		{
			e->getComponent<CAnimation>().animation.update();
		}
	}

	//TRY to get rid of equal signs in if statements
	if ((m_player->getComponent<CTransform>().velocity.x < 0 && m_player->getComponent<CTransform>().scale.x > 0)
	  || (m_player->getComponent<CTransform>().velocity.x > 0 && m_player->getComponent<CTransform>().scale.x < 0))
	{
		m_player->getComponent<CTransform>().scale.x *= -1;
	}
	
			
}

void Scene_Play::onEnd()
{
	//TODO: when the scene ends, change back to the MENU scene
	//		use m_game->changeScene(correct params);
}

void Scene_Play::sRender()
{
	//color the background darker so you know that the game is paused
	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	//set the viewport of the window to be centered on the player if it's far enough right
	auto& pPos = m_player->getComponent<CTransform>().pos;
	float windowCenterX = std::max(m_game->window().getSize().x / 2.0f, pPos.x);
	sf::View view = m_game->window().getView();
	view.setCenter(windowCenterX, m_game->window().getSize().y - view.getCenter().y);
	m_game->window().setView(view);

	if (m_drawTextures)
	{
		for (std::shared_ptr<Entity> e : m_entityManager.getEntities()) // !! figure out why we can't write 'auto' instead of 'std::shared_ptr<Entity>'
		{
			auto& transform = e->getComponent<CTransform>();
			if (e->hasComponent<CAnimation>())
			{
				auto& animation = e->getComponent<CAnimation>().animation;
				animation.getSprite().setRotation(transform.angle);
				animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
				animation.getSprite().setScale(sf::Vector2<float>(transform.scale.x, transform.scale.y));
				m_game->window().draw(animation.getSprite());
			}
			else if (e->hasComponent<CShape>())
			{
				auto& circle = e->getComponent<CShape>().circle;
				circle.setRotation(transform.angle);
				circle.setPosition(transform.pos.x, transform.pos.y);
				m_game->window().draw(circle);
			}
		}
	}

	//draw all Entity collision bounding boxes with a rectangleshape
	if (m_drawCollision)
	{
		for (std::shared_ptr<Entity> e : m_entityManager.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
				rect.setPosition(transform.pos.x, transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				m_game->window().draw(rect);
			}
		}
	}

	//draw the grid so that students can easily bug
	if (m_drawGrid)  // !!
	{
		float leftX = m_game->window().getView().getCenter().x - m_game->window().getSize().x / 2;
		float rightX = leftX + m_game->window().getSize().x + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);   // 

		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			drawLine(sf::Vector2<float>(x, 0), sf::Vector2<float>(x, m_game->window().getSize().y));
		}

		for (float y = 0; y < m_game->window().getSize().y; y += m_gridSize.y)
		{
			drawLine(sf::Vector2<float>(leftX, m_game->window().getSize().y - y), sf::Vector2<float>(rightX, m_game->window().getSize().y - y));

			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);   // play with these values
				m_gridText.setString("(" + xCell + "," + yCell + ")");
				m_gridText.setPosition(x + 3, m_game->window().getSize().y - y - m_gridSize.y + 2);
				m_gridText.setCharacterSize(10);
				m_game->window().draw(m_gridText);
			}
		}
	}
}
//			end