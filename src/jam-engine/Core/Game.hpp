#ifndef JE_GAME_HPP
#define JE_GAME_HPP

#include <string>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "jam-engine/Core/Input.hpp"
#include "jam-engine/Graphics/TexManager.hpp"
#include "jam-engine/Physics/CollisionMaskManager.hpp"

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

	const std::string& getTitle() const;

	bool isFocused() const;

	void setFPSCap(int cap);

	int getFPSCap() const;

	int getFPS() const;

	double getExactFPS() const;

	Input& getInput();

	TexManager& getTexManager();

	CollisionMaskManager& masks();

	const CollisionMaskManager& masks() const;

	sf::RenderWindow& getWindow();

private:
	sf::RenderWindow window;
	sf::View view;
	std::unique_ptr<Level> level;
	std::string title;
	int currentFPS;
	double exactFPS;
	int FPSCap;
	Input input;
	TexManager texMan;
	CollisionMaskManager maskManager;
	bool focused;
	std::vector<std::unique_ptr<Level> > oldlevels;
};

}

#endif
