#include "TexManager.hpp"

#ifdef JE_DEBUG
	#include <iostream>
#endif

namespace je
{

TexManager::TexManager()
	:path("img")
{
}

TexManager::~TexManager()
{
	for (auto it = textures.begin(); it != textures.end(); ++it)
		delete it->second;
}

const sf::Texture& TexManager::get(const std::string& id)
{
	if (!textures[id])
	{
		textures[id] = new sf::Texture();
		textures[id]->loadFromFile(path + id);
#ifdef JE_DEBUG
		std::cout << "Loaded " << id << std::endl;
#endif
	}
	return *textures[id];
}

void TexManager::setPath(const std::string& pathname)
{
	path = pathname;
}

}
