#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

#include"MainMenu.h"

int main()
{

	// Create the main window

	sf::Vector2i screenDimensions(1920, 1080);

	sf::RenderWindow MENU(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Hoinoi village", sf::Style::Close | sf::Style::Resize);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	MENU.setKeyRepeatEnabled(false);
	MENU.setFramerateLimit(60);

	// set BG
	sf::RectangleShape background(sf::Vector2f(1920.f, 1080.f));
	Texture MainTexture;
	MainTexture.loadFromFile("bg/bg2 copy.png");
	background.setTexture(&MainTexture);

	/*************************** background game *****************************/

	sf::RectangleShape Pbackground(sf::Vector2f(1920.f, 1080.f));
	Texture PlayerTexture;
	PlayerTexture.loadFromFile("bg/bg6.png");
	Pbackground.setTexture(&PlayerTexture);

	

	/*************************** background about *****************************/

	sf::RectangleShape Abackground(sf::Vector2f(1080.f, 1920.f));
	Texture AboutTexture;
	AboutTexture.loadFromFile("img/bg/menu.png");
	Abackground.setTexture(&AboutTexture);

	/*************************** background score *****************************/

	sf::RectangleShape Sbackground(sf::Vector2f(1920.f, 1080.f));
	Texture ScoreTexture;
	ScoreTexture.loadFromFile("img/bg/menu.png");
	Sbackground.setTexture(&ScoreTexture);


	/***************************************************** game zone ***************************************************************/

	int frame = 0;
	int row = 0;
	int frameCounter = 0;

	/*************************** ÊÃéÒ§ player *****************************/
	sf::Texture pTexture;
	sf::Sprite player;
	sf::Clock clock;

	if (!pTexture.loadFromFile("png/hoinoi4..png"))
		std::cout << "Error could not load player image" << std::endl;
	player.setTexture(pTexture);
	player.setScale(0.5f, 0.6f);

	

	//Main Menu Open

	while (MENU.isOpen())
	{
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Left)
				{
					mainMenu.MoveLeft();
					break;
				}
				if (event.key.code == Keyboard::Right) {
					mainMenu.MoveRight();
					break;
				}
				if (event.key.code == Keyboard::Return) {
					RenderWindow Play(VideoMode(screenDimensions.x, screenDimensions.y), "HOINOI VILLAGE");
					RenderWindow Score(VideoMode(screenDimensions.x, screenDimensions.y), "HOINOI VILLAGE");
					RenderWindow About(VideoMode(screenDimensions.x, screenDimensions.y), "HOINOI VILLAGE");

					int x = mainMenu.MainMenuPressed();

					if (x == 1)
					{

						//Start the game loop
						while (Play.isOpen()) {
							clock.restart();
							sf::Event aevent;
							while (Play.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									Play.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										Play.close();
									}
								}
							}

							//Update model
							player.setTextureRect(sf::IntRect(641 * frame, 514 * row, 641, 514));

							if (frameCounter == 100) {
								frame = (frame + 1) % 4;
								frameCounter = 0;
							}
							frameCounter++;

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
								row = 2;
								player.move(0, 0.3f);
								
							}

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
								row = 3;
								player.move(-0.3f, 0);
							}

							if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
								row = 2;
								player.move(0.3f, 0);
								
							}

							 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
								row = 2;
								player.move(0, -0.3);
								
							}
							 if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
								player.move(0, 0);
								row = 1;
							}

							// Idle check
							else if (row == 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))row = 0;
							else if (row == 3 && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))row = 0;
						
							else if (row == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::E))row = 0;

							About.close();
							Score.close();
							Play.clear();

							
							
							Play.draw(Pbackground); //ÇÒ´ background
						
							Play.draw(player); //ÇÒ´ player
							

							Play.display();

						}
					}

					if (x == 2) {

						while (Score.isOpen()) {

							Event aevent;
							while (Score.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									Score.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										Score.close();
									}
								}
							}

							Play.close();
							Score.clear();
							About.close();

							Score.draw(Sbackground);

							Score.display();
						}
					}
					if (x == 3) {

						while (About.isOpen()) {

							Event aevent;
							while (About.pollEvent(aevent)) {
								if (aevent.type == Event::Closed) {
									About.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										About.close();
									}
								}
							}

							Play.close();
							Score.clear();
							About.clear();

							About.draw(Abackground);

							About.display();
						}
					}
					if (x == 4)
						MENU.close();
					break;

				}
			}
		}



		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();


	}

}