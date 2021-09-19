#include "player.h"
#include "Animation1.h"


player::player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation1(texture,imageCount, switchTime)
{
		this->speed = speed;
		row = 0;
		
		faceRight = true;
		body.setSize(sf::Vector2f(250.0f, 300.0f));
		body.setPosition(850.0f, 540.0f);
		body.setTexture(texture);
}
player::~player()
{

}

void player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += speed * deltaTime;
	}
	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
	
		if (movement.x > 0.0f)
			row = 1;
		else
			row = 2;
	}

	animation1.Update(row, deltaTime);
	body.setTextureRect(animation1.uvRect);
	body.move(movement);

}
void player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
