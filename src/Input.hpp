#ifndef JE_INPUT_HPP
#define JE_INPUT_HPP

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#define AXES 8

namespace sf
{
class RenderWindow;
}
namespace je
{

class Input
{
public:
	static const float joyAxisThreshhold;

	Input(sf::RenderWindow& window);

	void update();
	void setFocus(bool focus);

	/*			keyboard		*/
	bool isKeyPressed(sf::Keyboard::Key key) const;
	bool isKeyReleased(sf::Keyboard::Key key) const;
	bool isKeyHeld(sf::Keyboard::Key key) const;

	bool testKey(sf::Keyboard::Key& output);

	/*			mouse			*/
	bool isButtonPressed(sf::Mouse::Button button) const;
	bool isButtonReleased(sf::Mouse::Button button) const;
	bool isButtonHeld(sf::Mouse::Button button) const;

	bool testButton(sf::Mouse::Button& output);

	/*			joystick		*/
	bool isJoyButtonPressed(unsigned int joyID, unsigned int button) const;
	bool isJoyButtonReleased(unsigned int joyID, unsigned int button) const;
	bool isJoyButtonHeld(unsigned int JoyID, unsigned int button) const;

	/**
	 * Checks for which button is pressed on which joystick
	 * @param joyID Which joystick to poll
	 # @param button Which button was pressed (OUTPUT - invalid if returns false)
	 * @return whether or not any joystick was pressing any button
	 */
	bool testJoyButton(unsigned int joyID, unsigned int& button) const;

	bool isJoyAxisPressed(unsigned int joyID, sf::Joystick::Axis axis, bool negative = false) const;
	bool isJoyAxisReleased(unsigned int joyID, sf::Joystick::Axis axis, bool negative = false) const;
	bool isJoyAxisHeld(unsigned int joyID, sf::Joystick::Axis axis, bool negative = false) const;

	float axisPos(unsigned int joyID, sf::Joystick::Axis axis) const;

	/**
	 * Checks which joystick is currently pressing buttons
	 * @param joyID Which joysticks ID is in use (OUTPUT - invalid if returns false)
	 * @return Whether or not a controller was found
	 */
	bool findController(unsigned int& joyID) const;

	/**
	 * Checks for which button is pressed on which joystick
	 * @param joyID Which joystick to poll
	 * @param output Which axis was pressed (OUTPUT - invalid if returns false)
	 * @param negative Whether the axis was detected in the positive or negative region
	 * @return whether or not any joystick was pressing any axis
	 */
	bool testAxis(unsigned int joyID, sf::Joystick::Axis& output, bool& negative) const;

private:
	int buttonUp[sf::Mouse::ButtonCount];
	int buttonDown[sf::Mouse::ButtonCount];
	int keyUp[sf::Keyboard::KeyCount];
	int keyDown[sf::Keyboard::KeyCount];
	int joyUp[sf::Joystick::Count][sf::Joystick::ButtonCount];
	int joyDown[sf::Joystick::Count][sf::Joystick::ButtonCount];
	int posAxisUp[sf::Joystick::Count][AXES];
	int posAxisDown[sf::Joystick::Count][AXES];
	int negAxisUp[sf::Joystick::Count][AXES];
	int negAxisDown[sf::Joystick::Count][AXES];
	sf::RenderWindow& window;
	bool focused;
};

}

#endif

