#ifndef JE_ANIMATION_HPP
#define JE_ANIMATION_HPP

#include <vector>
#include <string>
#include <initializer_list>
#include <SFML/Graphics.hpp>

namespace je
{
//	TODO: make not shit
class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation(const sf::Texture& texture, int width, int height, int time, bool repeat = true);
	Animation(const sf::Texture& texture, int width, int height, std::initializer_list<unsigned int> times, bool repeat = true);


	bool isFinished() const;

	bool advanceFrame();

	/**
	 * If animation isn't repeating, then set it back to the start
	 */
	void reset();

	//	sf::Drawable
	void draw (sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void updateTextureRect();

	sf::Sprite sprite;
	std::vector<unsigned int> lengths;
	unsigned int frameProgress;
	unsigned int frame;
	bool repeating;
	int width;
	int height;
};

} // je

#endif // JE_ANIMATION_HPP
