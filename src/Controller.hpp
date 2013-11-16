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
			Joystick,
			JoyAxis,
			Invalid
		};
		Bind();
		explicit Bind(sf::Keyboard::Key key);
		explicit Bind(sf::Mouse::Button button);
		explicit Bind(unsigned int joystickButton);
		explicit Bind(sf::Joystick::Axis axis, bool reversed = false);

		const unsigned int key;
		const Device device;
		const bool reversed;
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
	float axisPos(const std::string& axis) const;

	Bind getLastInputAsBind() const;

private:
	Input& input;
	unsigned int joyID;
	std::map<std::string, std::vector<Bind> > binds;
	std::map<std::string, sf::Joystick::Axis> boundAxes;
};

}

#endif
