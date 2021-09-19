#pragma once
#include<SFML\Graphics.hpp>
class Animation1
{
public:
	Animation1(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation1();


	void Update(int row, float deltaTime);


public:
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

