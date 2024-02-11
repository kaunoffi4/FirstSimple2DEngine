#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main(int argc, char* argv)
{
	Game game("config.txt");
	game.run();


}