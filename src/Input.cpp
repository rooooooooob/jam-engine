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
			keyDown[button] = 2;
			if (keyUp[button] > 0)
				--keyUp[button];
		}
		else
		{
			keyUp[button] = 2;
			if (keyDown[button] > 0)
				--keyDown[button];
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
/*			keyboard			*/
bool Input::isKeyPressed(sf::Keyboard::Key key) const
{
    return keyUp[key] == 1;
}

bool Input::isKeyReleased(sf::Keyboard::Key key) const
{
    return keyDown[key] == 1;
}

bool Input::isKeyHeld(sf::Keyboard::Key key) const
{
    return keyDown[key] == 2;
}

/*			mouse				*/
bool Input::isButtonPressed(sf::Mouse::Button button) const
{
    return buttonUp[button] == 1;
}

bool Input::isButtonReleased(sf::Mouse::Button button) const
{
    return buttonDown[button] == 1;
}

bool Input::isButtonHeld(sf::Mouse::Button button) const
{
    return buttonDown[button] == 2;
}

sf::Vector2f Input::getMousePos() const
{
	sf::Vector2i posI = window.mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
	return sf::Vector2f(posI.x, posI.y);
}

/*			joystick			*/
bool Input::isJoyButtonPressed(unsigned int joyID, unsigned int button) const
{
    return joyUp[joyID][button] == 1;
}

bool Input::isJoyButtonReleased(unsigned int joyID, unsigned int button) const
{
    return joyDown[joyID][button] == 1;
}

bool Input::isJoyButtonHeld(unsigned int joyID, unsigned int button) const
{
    return joyDown[joyID][button] == 2;
}
float Input::axis(int joyID, sf::Joystick::Axis axis) const
{
	return sf::Joystick::getAxisPosition(joyID, axis) / 100.f;
}

}
