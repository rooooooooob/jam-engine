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

class Level;

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
	struct AxisBind
	{
		enum class Device
		{
			Mouse,
			JoyAxis
		};
		enum class MouseAxis
		{
			X,
			Y
		};
		struct Interval
		{
			Interval();	//	[-1, 1]
			Interval(float min, float max);	//	custom
			const float min, max;
		};
		/**
		 * Binds mice axes
		 * @param axis Which mouse axis to use for axis
		 * @param rev Whether or not the Y axis is reversed
		 * @param interlval The interval to use (relative to pos!) for axis
		 * @param pos The position to use as the origin (this reference is used later, so don't pass temporaries!)
		 */
		AxisBind(MouseAxis axis, bool rev, Interval interval, const float *pos);
		/**
		 * Binds joystick axes
		 * @param axis Which axis to use for X asis
		 * @param rev Whether the X axis should be reversed
		 * @param interval The interval to operate on (default [-1, 1])
		 */
		AxisBind(sf::Joystick::Axis axis, bool rev, Interval = Interval());

		const Device device;
		const union
		{
			MouseAxis mAxis;
			sf::Joystick::Axis jAxis;
		};
		const bool reversed;
		const Interval interval;
		const float *pos;//used for mice
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
	void setAxis(const std::string& name, const AxisBind& bind);
	float axisPos(const std::string& axis, je::Level *level = nullptr) const;

	Bind getLastInputAsBind() const;

private:
	Input& input;
	unsigned int joyID;
	std::map<std::string, std::vector<Bind> > binds;
	std::map<std::string, AxisBind> boundAxes;
};

}

#endif
