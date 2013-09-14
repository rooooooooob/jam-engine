#include "Input.hpp"

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <SFML/Graphics/RenderWindow.hpp>

namespace je
{

Input::Input(sf::RenderWindow& window)
	:window(window)
	,focused(true)
{
    for (int& i : keyUp)
		i = 0;
	for (int& i : keyDown)
		i = 0;
	for (int& i : buttonUp)
		i = 0;
	for (int& i : buttonDown)
		i = 0;
	for (int joystick = 0; joystick < sf::Joystick::Count; ++joystick)
	{
		for (int& i : joyUp[joystick])
			i = 0;
		for (int& i : joyDown[joystick])
			i = 0;
	}
}

void Input::update()
{
	for (int key = 0; key < sf::Keyboard::KeyCount; ++key)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) key))
		{
			keyDown[key] = 2;
			if (keyUp[key] > 0)
				--keyUp[key];
		}
		else
		{
			keyUp[key] = 2;
			if (keyDown[key] > 0)
				--keyDown[key];
		}
	}
	for (int button = 0; button < sf::Mouse::ButtonCount; ++button)
	{
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button) button))
		{
			buttonDown[button] = 2;
			if (buttonUp[button] > 0)
				--buttonUp[button];
		}
		else
		{
			buttonUp[button] = 2;
			if (buttonDown[button] > 0)
				--buttonDown[button];
		}
	}
	for (int joystick = 0; joystick < sf::Joystick::Count; ++joystick)
	{
		for (int button = 0; button < sf::Joystick::ButtonCount; ++button)
		{
			if (sf::Joystick::isButtonPressed(joystick, button))
			{
				joyDown[joystick][button] = 2;
				if (joyUp[joystick][button] > 0)
					--joyUp[joystick][button];
			}
			else
			{
				joyUp[joystick][button] = 2;
				if (joyDown[joystick][button] > 0)
					--joyDown[joystick][button];
			}
		}
	}
}

void Input::setFocus(bool focus)
{
	focused = focus;
}

/*			keyboard			*/
bool Input::isKeyPressed(sf::Keyboard::Key key) const
{
    return focused && keyUp[key] == 1;
}

bool Input::isKeyReleased(sf::Keyboard::Key key) const
{
    return focused && keyDown[key] == 1;
}

bool Input::isKeyHeld(sf::Keyboard::Key key) const
{
    return focused && keyDown[key] == 2;
}

/*			mouse				*/
bool Input::isButtonPressed(sf::Mouse::Button button) const
{
    return focused && buttonUp[button] == 1;
}

bool Input::isButtonReleased(sf::Mouse::Button button) const
{
    return focused && buttonDown[button] == 1;
}

bool Input::isButtonHeld(sf::Mouse::Button button) const
{
    return focused && buttonDown[button] == 2;
}

/*			joystick			*/
bool Input::isJoyButtonPressed(unsigned int joyID, unsigned int button) const
{
    return focused && joyUp[joyID][button] == 1;
}

bool Input::isJoyButtonReleased(unsigned int joyID, unsigned int button) const
{
    return focused && joyDown[joyID][button] == 1;
}

bool Input::isJoyButtonHeld(unsigned int joyID, unsigned int button) const
{
    return focused && joyDown[joyID][button] == 2;
}
float Input::axis(int joyID, sf::Joystick::Axis axis) const
{
	return sf::Joystick::getAxisPosition(joyID, axis) / 100.f;
}

}
