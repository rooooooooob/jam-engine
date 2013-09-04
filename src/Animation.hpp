#ifndef LD_ANIMATION_HPP
#define LD_ANIMATION_HPP

#include <vector>
#include <string>
#include <initializer_list>
#include <SFML/Graphics.hpp>

namespace je
{

class Animation
{
public:
	Animation(const std::string& fname, int width, int height, std::initializer_list<unsigned int> times, bool repeat = true);

	void advanceFrame();

	void draw(sf::RenderTarget& target) const;

private:
	std::vector<sf::Sprite> frames;
	std::vector<unsigned int> lengths;
	unsigned int frameProgress;
	unsigned int frame;
	bool repeating;
};

}

#endif