#include "Input.hpp"

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <initializer_list>
#include <SFML/Graphics/RenderWindow.hpp>

namespace je
{

const float Input::joyAxisThreshhold = 0.2;

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
		for (int& i : posAxisUp[joystick])
			i = 0;
		for (int& i : posAxisDown[joystick])
			i = 0;
		for (int& i : negAxisUp[joystick])
			i = 0;
		for (int& i : negAxisDown[joystick])
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
		for (int axis = 0; axis < AXES; ++axis)
		{
			if (axisPos(joystick, (sf::Joystick::Axis) axis) > joyAxisThreshhold)
			{
				posAxisDown[joystick][axis] = 2;
				if (posAxisUp[joystick][axis] > 0)
					--posAxisUp[joystick][axis];
			}
			else
			{
				posAxisUp[joystick][axis] = 2;
				if (posAxisDown[joystick][axis] > 0)
					--posAxisDown[joystick][axis];
			}
			if (axisPos(joystick, (sf::Joystick::Axis) axis) < -joyAxisThreshhold)
			{
				negAxisDown[joystick][axis] = 2;
				if (negAxisUp[joystick][axis] > 0)
					--negAxisUp[joystick][axis];
			}
			else
			{
				negAxisUp[joystick][axis] = 2;
				if (negAxisDown[joystick][axis] > 0)
					--negAxisDown[joystick][axis];
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

bool Input::testKey(sf::Keyboard::Key& output)
{
	if (focused)
	{
		for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
		{
			if (keyDown[i] == 2)
			{
				output = (sf::Keyboard::Key) i;
				return true;
			}
		}
	}
	return false;
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

bool Input::testButton(sf::Mouse::Button& output)
{
	if (focused)
	{
		for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
		{
			if (buttonDown[i] == 2)
			{
				output = (sf::Mouse::Button) i;
				return true;
			}
		}
	}
	return false;
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

bool Input::testJoyButton(unsigned int joyID, unsigned int& button) const
{
	if (focused)
	{
		for (int i = 0; i < sf::Joystick::ButtonCount; ++i)
		{
			if (joyDown[joyID][i] == 2)
			{
				button = i;
				return true;
			}
		}
	}
	return false;
}

bool Input::isJoyAxisPressed(unsigned int joyID, sf::Joystick::Axis axis, bool negative) const
{
	return focused && (negative ? negAxisUp : posAxisUp)[joyID][axis] == 1;
}

bool Input::isJoyAxisReleased(unsigned int joyID, sf::Joystick::Axis axis, bool negative) const
{
	return focused && (negative ? negAxisDown : posAxisDown)[joyID][axis] == 1;
}

bool Input::isJoyAxisHeld(unsigned int joyID, sf::Joystick::Axis axis, bool negative) const
{
	return focused && (negative ? negAxisDown : posAxisDown)[joyID][axis] == 2;
}

float Input::axisPos(unsigned int joyID, sf::Joystick::Axis axis) const
{
	if (!sf::Joystick::hasAxis(joyID, axis))
		return 0;
	int val = sf::Joystick::getAxisPosition(joyID, axis);
	if (axis > 101 || axis < -101) // between -100 and 100 my ass, SFML!
		return 0;
	return val / 100.f;
}

bool Input::findController(unsigned int& joyID) const
{
	sf::Joystick::Axis axis;//just here so we can call testAxis()
	int foundCount = 0;
	for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
	{
		unsigned int foo;//just here so we can call testJoyButton()
		if (testJoyButton(i, foo))
		{
			joyID = i;
			++foundCount;
		}
		else if (testAxis(i, axis))
		{
			joyID = i;
			++foundCount;
		}
	}
	//if multiple ones are pressing shit then mark the input as invalid
	//and obviously if none were pressed then nothing was found
	return foundCount == 1;
}

bool Input::testAxis(unsigned int joyID, sf::Joystick::Axis& output) const
{
	std::initializer_list<sf::Joystick::Axis> axes = {
		sf::Joystick::Axis::X,
		sf::Joystick::Axis::Y,
		sf::Joystick::Axis::Z,
		sf::Joystick::Axis::R,
		sf::Joystick::Axis::U,
		sf::Joystick::Axis::V,
		sf::Joystick::Axis::PovX,
		sf::Joystick::Axis::PovY
	};
	for (sf::Joystick::Axis axis : axes)
	{
		if (abs(this->axisPos(joyID, axis)) > joyAxisThreshhold)
		{
			output = axis;
			return true;
		}
	}
	return false;
}

}
