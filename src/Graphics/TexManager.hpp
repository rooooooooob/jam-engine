#ifndef TEXMANAGER_HPP
#define TEXMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

namespace je
{

class TexManager
{
public:
	TexManager();
	~TexManager();

	const sf::Texture& get(const std::string& id);

	void setPath(const std::string& pathname);

private:

	std::unordered_map<std::string, sf::Texture*> textures;

	std::string path;
};

}

#endif
