#include "jam-engine/Graphics/Animation.hpp"

#include "jam-engine/Graphics/TexManager.hpp"

namespace je
{

Animation::Animation(const sf::Texture& texture, int width, int height, int time, bool repeat)
	:sprite(texture, sf::IntRect(0, 0, width, height))
	,frameProgress(0)
	,frame(0)
	,repeating(repeat)
	,width(width)
	,height(height)
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
	,width(width)
	,height(height)
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
			updateTextureRect();
			return true;
		}
		else
		{
			if (repeating)
			{
				frameProgress -= lengths[frame];
				frame = 0;
				updateTextureRect();
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
	updateTextureRect();
}

//	sf::Drawable

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!lengths.empty())//frame >= 0 && frame < lengths.size())
		target.draw(sprite, states);
}

/*					private					*/
void Animation::updateTextureRect()
{
	sprite.setTextureRect(sf::IntRect(width * frame, 0, width, height));
}

} // je
