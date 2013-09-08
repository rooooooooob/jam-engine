#ifndef JE_BACKGROUND_HPP
#define JE_BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

namespace je
{

template <typename T>
class Background : public Entity
{
public:
	Background(const T& fill, sf::Rect<int>& region, bool isRepeating = true);

	void update() override;
	void draw(sf::RenderTarget& target) const override;
	//void setRepeating();
	//bool isRepeating() const;
	void setVisibleRegion(sf::Rect<int>& region);
private:
	T fill;
	bool repeating;
	sf::Rect<int> region;
};

template <typename T>
Background<T>::Background(const T& fill, sf::Rect<int>& region, bool isRepeating)
	:fill(fill)
	,repeating(isRepeating)
	,region(region)
{

}

template <typename T>
void Background<T>::update()
{
}

template <typename T>
void Background<T>::draw(sf::RenderTarget& )

}

#endif // JE_BACKGROUND_HPP
