#include <iostream>
#include "player.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "Platform.h"



int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Tuturail", sf::Style::Close | sf::Style::Resize);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("png/hoinoi.png");
	player player(&playerTexture, sf::Vector2u(4, 7), 0.4f,100.0f);
	float deltaTime = 0.0f;
	sf::Clock clock;
	
	sf::Texture foresttext;
	foresttext.loadFromFile("png/bg1.png");
	Platform forest(&foresttext, sf::Vector2f(1920.0f, 1080.0f), sf::Vector2f(1920.0f / 2, 1080.0f / 2));




	
	while (window.isOpen())
{
	deltaTime = clock.restart().asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}

	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		}
	}
	player.Update(deltaTime);
	window.clear();
	forest.Draw(window);
	player.Draw(window);
	window.display();
	
}

return 0;
}

