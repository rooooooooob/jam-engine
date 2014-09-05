#include "jam-engine/Graphics/Animation.hpp"

#include "jam-engine/Graphics/TexManager.hpp"

namespace je
{

Animation::Animation(const sf::Texture& texture, int width, int height, int time, bool repeat)
	:sprite(texture, sf::IntRect(0, 0, width, height))
	,frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	const int length = texture.getSize().x / width;
	for (int i = 0, x = 0; i < length; ++i, x += width)
	{
		lengths.push_back(time);
	}
}

Animation::Animation(const sf::Texture& texture, int width, int height, std::initializer_list<unsigned int> times, bool repeat)
	:sprite(texture, sf::IntRect(0, 0, width, height))
	,frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	for (unsigned int length : times)
	{
		lengths.push_back(length);
	}
}

bool Animation::isFinished() const
{
	return !repeating && (frame == lengths.size() - 1);
}

bool Animation::advanceFrame()
{
	if (++frameProgress >= lengths[frame])
	{
		if (frame < lengths.size() - 1)
		{
			frameProgress -= lengths[frame];
			++frame;
			return true;
		}
		else
		{
			if (repeating)
			{
				frameProgress -= lengths[frame];
				frame = 0;
			}
			else
			{
				frameProgress = 0;
			}
		}
	}
	return false;
}

void Animation::reset()
{
	frame = 0;
}

//	sf::Drawable

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!lengths.empty())//frame >= 0 && frame < lengths.size())
		target.draw(sprite, states);
}

//	sf::Transformable
//void Animation::setRotation(float angle)
//{
//	sprite.setRotation(float angle);
//}
//
//void Animation::setScale(float xscale, float yscale)
//{
//	sprite.setScale(xscale, yscale);
//}
//
//void Animation::setScale(sf::Vector2f& factors)
//{
//	sprite.setScale(factors);
//}
//
//void Animation::setPosition(int x, int y)
//{
//	sprite.setPosition(x, y);
//}
//
//void Animation::setPosition(const sf::Vector2f& pos)
//{
//	sprite.setPosition(pos);
//}
//
//void Animation::setOrigin(float x, float y)
//{
//	sprite.setOrigin(x, y);
//}
//
//void Animation::setOrigin(const sf::Vector2f& origin)
//{
//	sprite.setOrigin(origin);
//}
//
//const sf::Vector2f& Animation::getPosition() const
//{
//	return sprite.getPosition();
//}
//
//float Animation::getRotation() const
//{
//	return sprite.getRotation();
//}
//
//const sf::Vector2f& Animation::getScale() const
//{
//	sprite.getScale();
//}
//
//const sf::Vector2f& Animation::getOrigin() const
//{
//	return sprite.getOrigin();
//}
//
//void Animation::move(float x, float y)
//{
//	sprite.move(x, y);
//}
//
//void Animation::move(const sf::Vector2f& offset)
//{
//	sprite.move(offset);
//}
//
//void Animation::rotate(float angle)
//{
//	sprite.rotate(angle);
//}
//
//void Animation::scale(float x, float y)
//{
//	sprite.scale(x, y);
//}
//
//void Animation::scale(const sf::Vector2f& factors)
//{
//	sprite.scale(factors);
//}
//
//const sf::Transform& Animation::getTransform() const
//{
//	return sprite.getTransform();
//}
//
//const sf::Transform& Animation::getInverseTransform() const
//{
//	return sprite.getInverseTransform();
//}

} // je
