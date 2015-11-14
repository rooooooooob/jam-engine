#ifndef JE_TEXMANAGER_HPP
#define JE_TEXMANAGER_HPP

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>


namespace je
{

class TexManager
{
public:
	TexManager();

	const sf::Texture& get(const std::string& id);

	void setPath(const std::string& pathname);

private:

	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;

	std::string path;
};

} // je

#endif // JE_TEXMANAGER_HPP
