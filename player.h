#pragma once
#include <SFML\Graphics.hpp>
#include "Animation1.h"
class player
{
public:
	player(sf::Texture* texture, sf::Vector2u imageCount, float switchTim,float speed);
	~player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape body;
	Animation1 animation1;
	unsigned int row;
	float speed;
	bool faceRight;


};

