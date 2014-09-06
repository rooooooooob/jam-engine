#ifndef LD_ANIMATION_HPP
#define LD_ANIMATION_HPP

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
	//	sf::Transformable
//	void setRotation(float angle) override;
//
//	void setScale(float xscale, float yscale) override;
//
//	void setScale(sf::Vector2f& factors) override;
//
//	void setPosition(int x, int y) override;
//
//	void setPosition(const sf::Vector2f& pos) override;
//
//	void setOrigin(float x, float y) override;
//
//	void setOrigin(const sf::Vector2f& origin) override;
//
//	const sf::Vector2f& getPosition() const override;
//
//	float getRotation() const override;
//
//	const sf::Vector2f& getScale() const override;
//
//	const sf::Vector2f& getOrigin() const override;
//
//	void move(float x, float y) override;
//
//	void move(const sf::Vector2f& offset) override;
//
//	void rotate(float angle) override;
//
//	void scale(float x, float y) override;
//
//	void scale(const sf::Vector2f& factors) override;
//
//	const sf::Transform& getTransform() const override;
//
//	const sf::Transform& getInverseTransform() const override;

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

}

#endif
