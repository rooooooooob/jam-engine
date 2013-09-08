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
	Animation(const sf::Texture& texture, int width, int height, int time, bool repeat = true);
	Animation(const sf::Texture& texture, int width, int height, std::initializer_list<unsigned int> times, bool repeat = true);


	bool isFinished() const;

	void advanceFrame();

	/**
	 * If animation isn't repeating, then set it back to the start
	 */
	void reset();

	void draw(sf::RenderTarget& target) const;

	template <typename F>
	void apply(F function);

private:
	std::vector<sf::Sprite> frames;
	std::vector<unsigned int> lengths;
	unsigned int frameProgress;
	unsigned int frame;
	bool repeating;
};

template <typename F>
void Animation::apply(F function)
{
	for (sf::Sprite& sprite : frames)
		function(sprite);
}

}

#endif
