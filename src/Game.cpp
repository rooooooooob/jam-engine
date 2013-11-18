#include "Game.hpp"

#include "Level.hpp"
#include "TexManager.hpp"

#include <iostream>
#include <chrono>

#ifndef JE_FPS_APPROX_RATE
	#define JE_FPS_APPROX_RATE 10
#endif

namespace je
{

Game::Game(int width, int height, int framerate)
	:window(sf::VideoMode(width, height), "")
	,view(sf::Vector2f(width / 2, height / 2), sf::Vector2f(width, height))
	,level()
	,input(window)
	,focused(true)
	,currentFPS(0)
	,exactFPS(0.f)
{
	this->setFPSCap(framerate);
}

Game::~Game()
{
}

int Game::execute()
{
	std::chrono::high_resolution_clock::time_point lastTime, lastTimeExact;
	int counter = 0;
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
		oldlevels.clear();

		window.display();

		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> frameTime = std::chrono::duration_cast<std::chrono::duration<double> >(currentTime - lastTimeExact);
		exactFPS = frameTime.count() ? 1.0 / frameTime.count() : 123456789;
		lastTimeExact = currentTime;
		if (++counter % 10 == 0)
		{
			frameTime = std::chrono::duration_cast<std::chrono::duration<double> >(currentTime - lastTime);
			currentFPS = frameTime.count() ? JE_FPS_APPROX_RATE / frameTime.count() : 123456789;
			lastTime = currentTime;
		}
	}

	return 0;
}

void Game::setLevel(Level *level)
{
	oldlevels.push_back(std::move(this->level));
	this->level.reset(level);
}

void Game::setTitle(const std::string& title)
{
	this->title = title;
	window.setTitle(title);
}

const std::string& Game::getTitle() const
{
	return title;
}

void Game::setFPSCap(int cap)
{
	window.setFramerateLimit(cap);
	FPSCap = cap;
}

int Game::getFPSCap() const
{
	return FPSCap;
}

int Game::getFPS() const
{
	return currentFPS;
}

double Game::getExactFPS() const
{
	return exactFPS;
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
