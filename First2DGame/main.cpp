#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <iostream>



int main(int argc, char* argv)
{
	GameEngine game("bin/assets.txt");
	game.run();



	//sf::RenderWindow window(sf::VideoMode(1280, 720), "Hope");

	//sf::Event event;

	///*sf::Texture texture;
	//texture.loadFromFile("bin/images/megaman/blocks.png");

	//sf::Sprite sprite(texture);
	//sprite.scale(sf::Vector2<float>(12, 12));*/
	//
	//

	//while (window.isOpen())
	//{
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::EventType::Closed)
	//		{
	//			window.close();
	//		}
	//	}
	//	window.clear();
	//	window.draw(sprite);
	//	window.display();
	//}

}