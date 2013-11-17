#include "Game.hpp"

#include "Level.hpp"
#include "TexManager.hpp"

#include <iostream>

namespace je
{

Game::Game(int width, int height, int framerate)
	:window(sf::VideoMode(width, height), "")
	,view(sf::Vector2f(width / 2, height / 2), sf::Vector2f(width, height))
	,level(nullptr)
	,input(window)
	,focused(true)
{
	window.setFramerateLimit(framerate);
}

Game::~Game()
{
    for (Level* l : oldlevels)
        delete l;
	oldlevels.clear();
	if (level)
		delete level;
}

int Game::execute()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (event.type == sf::Event::GainedFocus)
				focused = true;
			else if (event.type == sf::Event::LostFocus)
				focused = false;
		}

		window.clear();

		input.update();

		if (level)
		{
			level->update();

			view.setCenter(level->getCameraPosition());

			window.setView(view);

			level->draw(window);

			window.setView(window.getDefaultView());

			level->drawGUI(window);
		}

		window.display();

		for (Level* l : oldlevels)
        {
            std::cout << "deleting old levels";
            delete l;
        }
		oldlevels.clear();
	}

	return 0;
}

void Game::setLevel(Level *level)
{
	if (this->level)
		oldlevels.push_back (this->level);
	this->level = level;
}

void Game::setTitle(const std::string& title)
{
	this->title = title;
	window.setTitle(title);
}

Input& Game::getInput()
{
	return input;
}

TexManager& Game::getTexManager()
{
	return texMan;
}

sf::RenderWindow& Game::getWindow()
{
	return window;
}

}
