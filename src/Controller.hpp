#ifndef JE_CONTROLLER_HPP
#define JE_CONTROLLER_HPP

#include <vector>
#include <string>
#include <initializer_list>
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Input.hpp"

namespace je
{

class Controller
{
public:
	struct Bind
	{
		enum class Device
		{
			Keyboard,
			Mouse,
			Joystick
		};
		explicit Bind(sf::Keyboard::Key key);
		explicit Bind(sf::Mouse::Button button);
		explicit Bind(unsigned int joystickButton);

		const unsigned int key;
		const Device device;
	};

	Controller(Input& input, unsigned int joyID = 0);

	bool isActionPressed(const std::string& action) const;
	bool isActionReleased(const std::string& action) const;
	bool isActionHeld(const std::string& action) const;

	void addKeybind(const std::string& action, Bind bind);
	void setKeybinds(const std::string& action, std::initializer_list<Bind> binds);
	void removeKeybinds(const std::string& action);
	void removeKeybinds();

	/*		joystick specific		*/
	void setJoystickID(unsigned int id);
	float getAxis(sf::Joystick::Axis axis) const;
	sf::Vector2f getMousePos() const;

private:
	Input& input;
	unsigned int joyID;
	std::map<std::string, std::vector<Bind> > binds;
};

}

#endif
