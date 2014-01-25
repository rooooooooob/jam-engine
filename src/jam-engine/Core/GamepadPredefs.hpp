#ifndef JE_GAMEPAD_PREDEFS_HPP
#define JE_GAMEPAD_PREDEFS_HPP

#include "Controller.hpp"

namespace je
{

namespace Binds
{

namespace X360
{
const Controller::Bind A(0);
const Controller::Bind B(1);
const Controller::Bind Y(2);
const Controller::Bind X(3);
const Controller::Bind LB(4);
const Controller::Bind RB(5);
const Controller::Bind Back(6);
const Controller::Bind Start(7);
const Controller::Bind LStickIn(8);
const Controller::Bind RStickIn(9);
const Controller::Bind LT(sf::Joystick::Axis::Z);
const Controller::Bind RT(sf::Joystick::Axis::Z, true);
const Controller::Bind LStickLeft(sf::Joystick::Axis::X, true);
const Controller::Bind LStickRight(sf::Joystick::Axis::X);
const Controller::Bind LStickUp(sf::Joystick::Axis::Y, true);
const Controller::Bind LStickDown(sf::Joystick::Axis::Y);
const Controller::Bind RStickLeft(sf::Joystick::Axis::U, true);
const Controller::Bind RStickRight(sf::Joystick::Axis::U);
const Controller::Bind RStickUp(sf::Joystick::Axis::R, true);
const Controller::Bind RStickDown(sf::Joystick::Axis::R);
const Controller::Bind DPadDown(sf::Joystick::Axis::PovX, true);
const Controller::Bind DPadUp(sf::Joystick::Axis::PovX);
const Controller::Bind DPadLeft(sf::Joystick::Axis::PovY, true);
const Controller::Bind DPadRight(sf::Joystick::Axis::PovY);
}	//	namespace 360

namespace PS3
{
//	TODO: define later
}	//	namespace PS3

}	//	namespace Binds

}	//	namespace

#endif // JE_GAMEPAD_PREDEFS_HPP
