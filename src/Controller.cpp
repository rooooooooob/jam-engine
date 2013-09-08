#include "Controller.hpp"
#include <iostream>
namespace je
{
/*			bind			*/
Controller::Bind::Bind(sf::Keyboard::Key key)
	:key(key)
	,device(Device::Keyboard)
{
	std::cout << "Bind(Keyboard)\n";
}

Controller::Bind::Bind(sf::Mouse::Button button)
	:key(button)
	,device(Device::Mouse)
{
	std::cout << "Bind(Mouse)\n";
}

Controller::Bind::Bind(unsigned int joystickButton)
	:key(joystickButton)
	,device(Device::Joystick)
{
	std::cout << "Bind(Joystick)\n";
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
				(bind.device == Bind::Device::Joystick && input.isJoyButtonPressed(joyID, bind.key)))
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
				(bind.device == Bind::Device::Joystick && input.isJoyButtonReleased(joyID, bind.key)))
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
				(bind.device == Bind::Device::Joystick && input.isJoyButtonHeld(joyID, bind.key)))
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

float Controller::getAxis(sf::Joystick::Axis axis) const
{
	return input.axis(joyID, axis);
}

}
