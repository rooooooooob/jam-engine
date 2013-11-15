#ifndef JE_INPUT_HPP
#define JE_INPUT_HPP

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace sf
{
class RenderWindow;
}
namespace je
{

class Input
{
public:
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
	
	bool testButton(sf::Mouse::button& output);

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
	bool testJoyButton(int joyID, unsigned int& button) const;
	
	
	float axis(int joyID, sf::Joystick::Axis axis) const ;
	
	/**
	 * Checks which joystick is currently pressing buttons
	 * @param joyID Which joysticks ID is in use (OUTPUT - invalid if returns false)
	 * @return Whether or not a controller was found
	 */
	bool findController(unsigned int& joyID) const;
	
	/**
	 * Checks for which button is pressed on which joystick
	 * @param joyID Which joystick to poll
	 # @param axis Which axis was pressed (OUTPUT - invalid if returns false)
	 * @return whether or not any joystick was pressing any axis
	 */
	bool testAxis(int joyID, sf::Joystick::Axis& axis) const;
	
private:
	int buttonUp[sf::Mouse::ButtonCount];
	int buttonDown[sf::Mouse::ButtonCount];
	int keyUp[sf::Keyboard::KeyCount];
	int keyDown[sf::Keyboard::KeyCount];
	int joyUp[sf::Joystick::Count][sf::Joystick::ButtonCount];
	int joyDown[sf::Joystick::Count][sf::Joystick::ButtonCount];
	sf::RenderWindow& window;
	bool focused;
};

}

#endif

