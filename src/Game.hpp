#ifndef JE_GAME_HPP
#define JE_GAME_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "Input.hpp"
#include "TexManager.hpp"

namespace je
{

class Level;

class Game
{
public:
	Game(int width, int height, int framerate);
	~Game();

	int execute();

	void setLevel(Level *level);

	void setTitle(const std::string& title);

	bool isFocused() const;

	Input& getInput();

	TexManager& getTexManager();

	sf::RenderWindow& getWindow();

private:
	sf::RenderWindow window;
	sf::View view;
	Level *level;
	std::string title;
	Input input;
	TexManager texMan;
	bool focused;
};

}

#endif
