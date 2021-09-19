
#pragma once
#include <SFML\Graphics.hpp>

	class Platform
	{
	public:
		Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
		~Platform();
		void Draw(sf::RenderWindow& window);
		sf::RectangleShape body;

	private:

	};

