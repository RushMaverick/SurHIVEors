#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Constants.h"
#include "Game.h"
#include <memory>
#include <iostream>
#include "ResourceManager.h"

int main(int argc, char *argv[])
{
	// ResourceManager Must be Instantiated here -- DO NOT CHANGE
	ResourceManager::init(argv[0]);
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SurHIVEors");
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(30);

	std::unique_ptr<Game> pGame = std::make_unique<Game>();
	if (!pGame->initialise())
	{
		std::cerr << "Game Failed to initialise" << std::endl;
		return 1;
	}
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				pGame->keyIsPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				pGame->keyIsReleased(event.key.code);
				break;
			default:
				break;
			}
		}
		elapsedTime = clock.getElapsedTime();
		pGame->update(window, elapsedTime.asSeconds());
		window.clear(sf::Color::Black);
		window.draw(*pGame.get());
		clock.restart();
		window.display();
	}

	return 0;
}
