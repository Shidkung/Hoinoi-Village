#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("Font/Scary House.ttf")) {
		std::cout << "No font is here" << std::endl;
	}

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color(43, 4, 4, 255));
	mainMenu[1].setOutlineColor(sf::Color(15, 128, 71, 255));
	mainMenu[1].setOutlineThickness(3);
	mainMenu[1].setString("START");
	mainMenu[1].setCharacterSize(60);
	mainMenu[1].setLetterSpacing(3);
	mainMenu[1].setPosition(300, 550);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color(43, 4, 4, 255));
	mainMenu[2].setOutlineColor(sf::Color(15, 128, 71, 255));
	mainMenu[2].setOutlineThickness(3);
	mainMenu[2].setString("SCORE");
	mainMenu[2].setCharacterSize(60);
	mainMenu[2].setLetterSpacing(3);
	mainMenu[2].setPosition(650, 550);

	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color(43, 4, 4, 255));
	mainMenu[3].setOutlineColor(sf::Color(15, 128, 71, 255));
	mainMenu[3].setOutlineThickness(3);
	mainMenu[3].setString("ABOUT");
	mainMenu[3].setCharacterSize(60);
	mainMenu[3].setLetterSpacing(3);
	mainMenu[3].setPosition(1000, 550);

	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(sf::Color(43, 4, 4, 255));
	mainMenu[4].setOutlineColor(sf::Color(15,128,71,255));
	mainMenu[4].setOutlineThickness(3);
	mainMenu[4].setString("EXIT");
	mainMenu[4].setCharacterSize(60);
	mainMenu[4].setLetterSpacing(3);
	mainMenu[4].setPosition(1350, 550);


	MainMenuSelected = 0;

}

MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 1; i < Max_main_menu; i++) {
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveLeft()
{

	if (MainMenuSelected - 1 >= 0) {

		mainMenu[MainMenuSelected].setOutlineColor(sf::Color(15, 128, 71, 255));
		mainMenu[MainMenuSelected].setOutlineThickness(3);
		mainMenu[MainMenuSelected].setFillColor(sf::Color(43, 4, 4, 255));

		MainMenuSelected--;

		if (MainMenuSelected == 0) {
			MainMenuSelected = 4;
		}

		mainMenu[MainMenuSelected].setFillColor(Color::Black);
		mainMenu[MainMenuSelected].setOutlineColor(Color::Red);
		mainMenu[MainMenuSelected].setOutlineThickness(3);

	}
}

//Move Right


void MainMenu::MoveRight()
{

	if (MainMenuSelected + 1 <= Max_main_menu) {

		mainMenu[MainMenuSelected].setOutlineColor(sf::Color(15, 128, 71, 255));
		mainMenu[MainMenuSelected].setOutlineThickness(3);
		mainMenu[MainMenuSelected].setFillColor(sf::Color(43, 4, 4, 255));
		MainMenuSelected++;

		if (MainMenuSelected == 5) {
			MainMenuSelected = 1;
		}

		mainMenu[MainMenuSelected].setFillColor(sf::Color::Black);
		mainMenu[MainMenuSelected].setOutlineColor(sf::Color::Red);
		mainMenu[MainMenuSelected].setOutlineThickness(3);
	}

}
