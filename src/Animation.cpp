#include "Animation.hpp"

#include "TexManager.hpp"

namespace je
{

Animation::Animation(const std::string& fname, int width, int height, std::initializer_list<unsigned int> times, bool repeat)
	:frameProgress(0)
	,frame(0)
	,repeating(repeat)
{
	const sf::Texture& texture = TexManager::get(fname);
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

}