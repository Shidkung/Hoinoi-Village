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
#include<cstdlib>
#include<cstdlib>

#include<vector>

using namespace sf;
#include"MainMenu.h"

int main()
{

	// Create the main window

	sf::Vector2i screenDimensions(1920, 1080);

	sf::RenderWindow Window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Hoinoi village", sf::Style::Close);
	MainMenu mainMenu(Window.getSize().x, Window.getSize().y);

	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);



	/****************************************** bullet ************************************************************/
	srand(time(NULL));
	Texture bulletTex;
	Sprite bullet;

	if (!bulletTex.loadFromFile("png/bullet.png"))
		std::cout << "Error could not load player image" << std::endl;
	bullet.setTexture(bulletTex);
	bullet.setScale(0.2f, 0.2f);

	std::vector<Sprite> bullets;

	/*********************************Score******************************************************************/
	Text scoreText;
	sf::Font font;
	font.loadFromFile("font/Scary Halloween Font.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(Color::Red);
	scoreText.setPosition(1400.f, 10.f);
	int score = 0;



	/*****************************************set Enermy*************************************************************/
	srand(time(NULL));

	//Zombie
	Texture zombieTex;
	Sprite zombie;

	if (!zombieTex.loadFromFile("png/enermy01.png"))
		throw "Could not load cat.png!";

	zombie.setTexture(zombieTex);
	zombie.setScale(Vector2f(2.f, 2.f));
	int zombieSpawnTimer = 15;

	std::vector<Sprite> zombies;
	zombies.push_back(Sprite(zombie));



	/********************************************enermy************************************************************/

	// set BG
	sf::RectangleShape background(sf::Vector2f(1920.f, 1080.f));
	Texture MainTexture;
	MainTexture.loadFromFile("bg/bg2 copy.png");
	background.setTexture(&MainTexture);

	/***************************************background game ******************************************************/

	sf::RectangleShape Pbackground(sf::Vector2f(1920.f, 1080.f));
	Texture PlayerTexture;
	PlayerTexture.loadFromFile("bg/bg6.png");
	Pbackground.setTexture(&PlayerTexture);



	/**************************************background about *****************************************************/

	sf::RectangleShape Abackground(sf::Vector2f(1920.f, 1080.f));
	Texture AboutTexture;
	AboutTexture.loadFromFile("bg/bg1.png");
	Abackground.setTexture(&AboutTexture);

	/************************************* background score ************************************************************************/

	sf::RectangleShape Sbackground(sf::Vector2f(1920.f, 1080.f));
	Texture ScoreTexture;
	ScoreTexture.loadFromFile("bg/bg.png");
	Sbackground.setTexture(&ScoreTexture);


	/***************************************************** game zone ***************************************************************/

	int frame = 0;
	int row = 0;
	int frameCounter = 0;

	/******************************************** load player *******************************************************************/
	sf::Texture pTexture;
	sf::Sprite player;
	sf::Clock clock;
	Texture playerTex;
	int hp = 10;
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Red);
	hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));
	hpBar.setPosition(200.f, 10.f);


	if (!pTexture.loadFromFile("png/hoinoiii.png"))
		std::cout << "Error could not load player image" << std::endl;
	player.setTexture(pTexture);
	player.setScale(0.4f, 0.6f);
	Vector2f playerCenter;
	int shootTimer = 0;
	float deltaTime;

	/******************************************************Main menu open**********************************************************************/
	goto MENU;
MENU:
	while (Window.isOpen())
	{
		Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				Window.close();
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


					int x = mainMenu.MainMenuPressed();

					if (x == 1)goto Play;
					else if (x == 2) goto Score;
					else if (x == 3) goto About;
					else if (x == 4)
						Window.close();
					break;

				}
			}
		}

		Window.clear();
		Window.draw(background);
		mainMenu.draw(Window);
		Window.display();


	}


/************************************************* play *************************************************************/

Play:
	while (Window.isOpen() && hp > 0) {
		//clock.restart();
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		playerCenter = Vector2f(player.getPosition().x + 150, player.getPosition().y + 125);
		sf::Event aevent;
		while (Window.pollEvent(aevent)) {
			if (aevent.type == Event::Closed) {
				Window.close();
			}
			if (aevent.type == Event::KeyPressed) {
				if (aevent.key.code == Keyboard::Escape) {
					goto MENU;

				}

			}
		}

		//(ENEMIES)
		int randY = 25;
		while (randY <= 200 || randY >= 800)
		{
			randY = rand();
		}
		for (size_t i = 0; i < zombies.size(); i++)
		{
			zombies[i].move(-300.f * deltaTime, 0.f);

			if (zombies[i].getPosition().x < 0 - zombie.getGlobalBounds().width)
				zombies.erase(zombies.begin() + i);
		}

		if (zombieSpawnTimer < 50)
			zombieSpawnTimer++;

		if (zombieSpawnTimer >= 50)
		{
			zombie.setPosition(Window.getSize().x, randY);
			zombies.push_back(Sprite(zombie));
			while (randY <= 200 || randY >= 2000)
			{
				randY = rand();
			}
			zombieSpawnTimer = 0;
		}

		//COLLISION ENERMY
		for (size_t i = 0; i < zombies.size(); i++)
		{
			if (player.getGlobalBounds().intersects(zombies[i].getGlobalBounds()))
			{
				hp--;
				zombies.erase(zombies.begin() + i);
			}
		}

		//UI
		hpBar.setSize(Vector2f((float)hp * 20.f, 20.f));





		//Collision

		if (player.getPosition().y > Window.getSize().y - 40 - player.getGlobalBounds().height)
			player.setPosition(player.getPosition().x, Window.getSize().y - 40 - player.getGlobalBounds().height);

		if (player.getPosition().y < 80)
			player.setPosition(player.getPosition().x, 80);




		//Update model
		player.setTextureRect(sf::IntRect(640 * frame, 555.6 * row, 640, 555.6));



		//PROJECTILES
		if (shootTimer < 20)
			shootTimer++;


		if (frameCounter == 10) {
			frame = (frame + 1) % 4;
			frameCounter = 0;
		}
		frameCounter++;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			row = 2;
			player.move(0, 300.f * deltaTime);

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			row = 3;
			player.move(-300.f * deltaTime, 0);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			row = 2;
			player.move(300.f * deltaTime, 0);

		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			row = 2;
			player.move(0, -300.f * deltaTime);

		}



		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && shootTimer >= 20) {

			row = 1;
			bullet.setPosition(playerCenter);
			bullets.push_back(bullet);
			shootTimer = 0;

		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].move(10.f, 0.f);

			if (bullets[i].getPosition().x >= 1920)
				bullets.erase(bullets.begin() + i);
		}

		

//Collision
		if (!zombies.empty() && !bullets.empty())
		{
			for (size_t i = 0; i < bullets.size(); i++)
			{
				for (size_t k = 0; k < zombies.size(); k++)
				{
					if (bullets[i].getGlobalBounds().intersects(zombies[k].getGlobalBounds()))
					{
						bullets.erase(bullets.begin() + i);
						zombies.erase(zombies.begin() + k);
						score++;
						break;
					}
				}
			}
		}


		scoreText.setString("Score : " + std::to_string(score));

		// Idle check
		if (row == 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))row = 0;
		if (row == 3 && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))row = 0;

		else if (row == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::E))row = 0;

		

		Window.clear();



		Window.draw(Pbackground); //ÇÒ´ background
		Window.draw(player); //ÇÒ´ player
		Window.draw(scoreText);
		for (size_t i = 0; i < zombies.size(); i++)
		{
			Window.draw(zombies[i]);
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			Window.draw(bullets[i]);
		}
		Window.draw(hpBar);
		Window.display();

	}
	goto MENU;

About:
	while (Window.isOpen()) {

		Event aevent;
		while (Window.pollEvent(aevent)) {
			if (aevent.type == Event::Closed) {
				Window.close();
			}
			if (aevent.type == Event::KeyPressed) {
				if (aevent.key.code == Keyboard::Escape) {
					goto MENU;
				}
			}
		}

		Window.clear();
		Window.draw(Abackground);
		Window.display();
	}


Score:
	while (Window.isOpen()) {

		Event aevent;
		while (Window.pollEvent(aevent)) {
			if (aevent.type == Event::Closed) {
				Window.close();
			}
			if (aevent.type == Event::KeyPressed) {
				if (aevent.key.code == Keyboard::Escape) {
					goto MENU;
				}
			}
		}

		Window.clear();
		Window.draw(Sbackground);
		Window.display();
	}


}






void Showtexet(int x, int y, string word, int size, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(size);
	window.draw(text);
}

void updatascore(string a, int b)
{
	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	vector <pair<int, string>> userScore;
	fp = fopen("./Score.txt", "r");
	if (fp == NULL)
		printf("File not found\n");

	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(make_pair(score[i], name[i]));
	}

	name[5] = a;
	score[5] = b;
	userScore.push_back(make_pair(score[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("Score.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);
}

void Showscoreboard(sf::RenderWindow& window)
{
	sf::Font font;
	font.loadFromFile("font/Scary Halloween Font.ttf");

	FILE* fp;
	char temp[255];
	int score[6];
	string name[6];
	fp = fopen("./Score.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		char no[3] = { '1' + i };
		no[1] = '.';
		no[2] = '\0';
		Showtexet(700, 350 + 100 * i, no, 50, window, &font);
		fscanf(fp, "%s", &temp);
		Showtexet(750, 350 + 100 * i, temp, 50, window, &font);
		fscanf(fp, "%d", &score[i]);
		char sc[10];
		int k = 0, j;
		if (score[i] == 0)
			sc[k++] = 48;
		while (score[i] > 0)
		{
			sc[k++] = score[i] % 10 + 48;
			score[i] /= 10;
		}
		sc[k] = '\0';
		char show[10];
		for (j = 0; j < strlen(sc); j++)
		{
			show[j] = sc[strlen(sc) - 1 - j];
		}
		show[j] = '\0';
		Showtexet(1100, 350 + 100 * i, show, 50, window, &font);
	}
	fclose(fp);
	//Cout
}
