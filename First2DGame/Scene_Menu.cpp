#include "Scene_Menu.h"
#include "Scene_Play.h"


#include <iostream>

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::init()
{
	setMenuStrings(0, "level 1");
	m_menuText[0].setFillColor(sf::Color::White);
	setMenuStrings(1, "level 2");
	setMenuStrings(2, "level 3");

	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Return, "ENTER");
}

void Scene_Menu::update()
{
	sRender();
}

void Scene_Menu::onEnd()
{
}

void Scene_Menu::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "UP") 
		{ 
				m_menuText[m_selectedMenuIndex].setFillColor(sf::Color::Red);
				if (m_selectedMenuIndex > 0)
				{
					m_selectedMenuIndex--;
				}
				else
				{
					m_selectedMenuIndex = MAX_NUMBER_OF_ITEMS - 1;
				}
				m_menuText[m_selectedMenuIndex].setFillColor(sf::Color::White);
		}
		else if (action.name() == "DOWN")
		{
			m_menuText[m_selectedMenuIndex].setFillColor(sf::Color::Red);
			if (m_selectedMenuIndex + 1 < MAX_NUMBER_OF_ITEMS)
			{
				m_selectedMenuIndex++;
			}
			else
			{
				m_selectedMenuIndex = 0;
			}
			m_menuText[m_selectedMenuIndex].setFillColor(sf::Color::White);
		}
		else if (action.name() == "ENTER")
		{
			switch (m_selectedMenuIndex)
			{
			case 0:
				m_game->changeScene("Scene_Play", std::make_shared<Scene_Play>(m_game, "bin/level1.txt"));
				std::cout << "Opened level1";
				break;
			case 1:
				m_game->changeScene("Scene_Play", std::make_shared<Scene_Play>(m_game, "bin/level2.txt"));
				std::cout << "Opened level2";
				break;
			case 2:
				m_game->changeScene("Scene_Play", std::make_shared<Scene_Play>(m_game, "bin/level3.txt"));
				std::cout << "Opened level3";
				break;
			}
		}
	}
	else
	{

	}
}

void Scene_Menu::setMenuStrings(int index, std::string name)
{
	m_menuText[index].setFont(m_game->assets().getFont("Arial"));
	m_menuText[index].setFillColor(sf::Color(255, 0, 0));
	m_menuText[index].setString(name);
	sf::FloatRect textRect = m_menuText[index].getLocalBounds();  // getGlobalBounds()
	m_menuText[index].setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_menuText[index].setPosition(100, m_game->window().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * (index + 1));
}

void Scene_Menu::sRender()
{
	for (size_t i = 0; i < MAX_NUMBER_OF_ITEMS; ++i)
	{
		m_game->window().draw(m_menuText[i]);
	}
}
