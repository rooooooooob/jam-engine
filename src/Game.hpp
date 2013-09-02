#ifndef JE_GAME_HPP
#define JE_GAME_HPP

#include <string>
#include <SFML/Graphics.hpp>

namespace je
{

class Level;

class Game
{
public:
	Game();
	~Game();

	int execute();

	void setLevel(Level *level);
	
	void setTitle(const std::string& title);

private:
	sf::RenderWindow window;
	Level *level;
	std::string title;
};

}

#endif