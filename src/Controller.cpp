#include "Controller.hpp"
#include <iostream>
namespace je
{
/*			bind			*/
Controller::Bind::Bind()
	:key(0)
	,device(Device::Invalid)
	,reversed(false)
{
}
Controller::Bind::Bind(sf::Keyboard::Key key)
	:key(key)
	,device(Device::Keyboard)
	,reversed(false)
{
	std::cout << "Bind(Keyboard)\n";
}

Controller::Bind::Bind(sf::Mouse::Button button)
	:key(button)
	,device(Device::Mouse)
	,reversed(false)
{
	std::cout << "Bind(Mouse)\n";
}

Controller::Bind::Bind(unsigned int joystickButton)
	:key(joystickButton)
	,device(Device::Joystick)
	,reversed(false)
{
	std::cout << "Bind(Joystick)\n";
}

Controller::Bind::Bind(sf::Joystick::Axis axis, bool reversed)
	:key(axis)
	,device(Device::JoyAxis)
	,reversed(reversed)
{
	std::cout << "Bind(JoyAxis)\n";
}



/*			controller			*/
Controller::Controller(Input& input, unsigned int joyID)
	:input(input)
	,joyID(joyID)
{
}


bool Controller::isActionPressed(const std::string& action) const
{
	auto it = binds.find(action);
	if (it != binds.end())
	{
		for (const Bind& bind : it->second)
		{
			if ((bind.device == Bind::Device::Keyboard && input.isKeyPressed((sf::Keyboard::Key) bind.key)) ||
				(bind.device == Bind::Device::Mouse && input.isButtonPressed((sf::Mouse::Button) bind.key)) ||
				(bind.device == Bind::Device::Joystick && input.isJoyButtonPressed(joyID, bind.key)) ||
				(bind.device == Bind::Device::JoyAxis && input.isJoyAxisPressed(joyID, (sf::Joystick::Axis) bind.key, bind.reversed)))
				return true;
		}
	}
	return false;
}

bool Controller::isActionReleased(const std::string& action) const
{
	auto it = binds.find(action);
	if (it != binds.end())
	{
		for (const Bind& bind : it->second)
		{
			if ((bind.device == Bind::Device::Keyboard && input.isKeyReleased((sf::Keyboard::Key) bind.key)) ||
				(bind.device == Bind::Device::Mouse && input.isButtonReleased((sf::Mouse::Button) bind.key)) ||
				(bind.device == Bind::Device::Joystick && input.isJoyButtonReleased(joyID, bind.key)) ||
				(bind.device == Bind::Device::JoyAxis && input.isJoyAxisReleased(joyID, (sf::Joystick::Axis) bind.key, bind.reversed)))
				return true;
		}
	}
	return false;
}

bool Controller::isActionHeld(const std::string& action) const
{
	auto it = binds.find(action);
	if (it != binds.end())
	{
		for (const Bind& bind : it->second)
		{
			if ((bind.device == Bind::Device::Keyboard && input.isKeyHeld((sf::Keyboard::Key) bind.key)) ||
				(bind.device == Bind::Device::Mouse && input.isButtonHeld((sf::Mouse::Button) bind.key)) ||
				(bind.device == Bind::Device::Joystick && input.isJoyButtonHeld(joyID, bind.key)) ||
				(bind.device == Bind::Device::JoyAxis && input.isJoyAxisHeld(joyID, (sf::Joystick::Axis) bind.key, bind.reversed)))
				return true;
		}
	}
	return false;
}



void Controller::addKeybind(const std::string& action, Bind bind)
{
	binds[action].push_back(bind);
}

void Controller::setKeybinds(const std::string& action, std::initializer_list<Bind> binds)
{
	this->binds[action].clear();
	for (Bind bind : binds)
		this->binds[action].push_back(bind);
}

void Controller::removeKeybinds(const std::string& action)
{
	binds[action].clear();
}

void Controller::removeKeybinds()
{
	binds.clear();
}


/*		joystick specific		*/
void Controller::setJoystickID(unsigned int id)
{
	joyID = id;
}

float Controller::axisPos(const std::string& axis) const
{
	auto it = boundAxes.find(axis);
	if (it == boundAxes.end())
		return 0;
	else
		return input.axisPos(joyID, it->second);
}

Controller::Bind Controller::getLastInputAsBind() const
{
	//	check keys
	sf::Keyboard::Key key;
	if (input.testKey(key))
		return Bind(key);
	//	check mouse buttons
	sf::Mouse::Button button;
	if (input.testButton(button))
		return Bind(button);
	//	check joypad buttons
	unsigned int joyButton;
	if (input.testJoyButton(joyID, joyButton))
		return Bind(joyButton);
	//	check joypad axes
	sf::Joystick::Axis axis;
	bool reversed;
	if (input.testAxis(joyID, axis, reversed))
		return Bind(axis, reversed);
	//	nothing was pressed, return empty bind (invalid)
	return Bind();
}

}
