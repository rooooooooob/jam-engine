#include "Animation.hpp"

#include "TexManager.hpp"

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

void Animation::advanceFrame()
{
	if (++frameProgress > lengths[frame])
	{
		if (frame < lengths.size() - 1)
		{
			frameProgress -= lengths[frame];
			++frame;
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
}

void Animation::draw(sf::RenderTarget& target) const
{
	if (!frames.empty())//frame >= 0 && frame < frames.size())
		target.draw(frames[frame]);
}

}
