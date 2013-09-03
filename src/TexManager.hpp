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
	static void load();
	static void unload();

	static const sf::Texture& get(const std::string& id);
private:
	TexManager();
	~TexManager();

	std::unordered_map<std::string, sf::Texture*> textures;

	static TexManager *man;
	static unsigned int references;
};

}

#endif
