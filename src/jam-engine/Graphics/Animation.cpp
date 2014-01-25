#include "jam-engine/Graphics/Animation.hpp"

#include "jam-engine/Graphics/TexManager.hpp"

namespace je
{

Animation::Animation(const sf::Texture& texture, int width, int height, int time, bool repeat)
	:frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	int length = texture.getSize().x / width;
	for (int i = 0, x = 0; i < length; ++i, x += width)
	{
		lengths.push_back(time);
		frames.push_back(sf::Sprite(texture, sf::IntRect(x, 0, width, height)));
	}
}

Animation::Animation(const sf::Texture& texture, int width, int height, std::initializer_list<unsigned int> times, bool repeat)
	:frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	int x = 0;
	for (unsigned int length : times)
	{
		lengths.push_back(length);
		frames.push_back(sf::Sprite(texture, sf::IntRect(x, 0, width, height)));
		x += width;
	}
}

bool Animation::isFinished() const
{
	return !repeating && frame == frames.size() - 1;
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
//	TODO: optimize
void Animation::setRotation(float angle)
{
	for (sf::Sprite& sprite : frames)
		sprite.setRotation(angle);
}
//	TODO: optimize
void Animation::setScale(float xscale, float yscale)
{
	for (sf::Sprite& sprite : frames)
		sprite.setScale(xscale, yscale);
}
//	TODO: optimize
void Animation::setPosition(int x, int y)
{
	for (sf::Sprite& sprite : frames)
		sprite.setPosition(x, y);
}

void Animation::setPosition(const sf::Vector2f& pos)
{
	for (sf::Sprite& sprite : frames)
		sprite.setPosition(pos);
}

//	sf::Drawable

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!frames.empty())//frame >= 0 && frame < frames.size())
		target.draw(frames[frame], states);
}

//	sf::Transformable

}