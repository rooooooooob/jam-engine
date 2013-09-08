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

	/*			keyboard		*/
    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isKeyReleased(sf::Keyboard::Key key) const;
    bool isKeyHeld(sf::Keyboard::Key key) const;

	/*			mouse			*/
	bool isButtonPressed(sf::Mouse::Button button) const;
	bool isButtonReleased(sf::Mouse::Button button) const;
	bool isButtonHeld(sf::Mouse::Button button) const;

	sf::Vector2f getMousePos() const;


	/*			joystick		*/
	bool isJoyButtonPressed(unsigned int joyID, unsigned int button) const;
	bool isJoyButtonReleased(unsigned int joyID, unsigned int button) const;
	bool isJoyButtonHeld(unsigned int JoyID, unsigned int button) const;

    float axis(int joyID, sf::Joystick::Axis axis) const ;

private:
	int keyUp[sf::Keyboard::KeyCount];
	int keyDown[sf::Keyboard::KeyCount];
	int buttonUp[sf::Mouse::ButtonCount];
	int buttonDown[sf::Mouse::ButtonCount];
	int joyUp[sf::Joystick::Count][sf::Joystick::ButtonCount];
	int joyDown[sf::Joystick::Count][sf::Joystick::ButtonCount];
	sf::RenderWindow& window;
};

}

#endif

