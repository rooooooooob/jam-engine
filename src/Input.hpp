#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/Window/Joystick.hpp>

namespace je
{

static const int PLAYERS = 4;
static const int BUTTONS = 9;

class Input
{
    public:
        typedef sf::Joystick::Axis Axis;
        enum Action {Right, Left, Jump, Crouch, Sword, Throw, Sprint, Up, Down};
        Input();
        ~Input();

        void update();

        static bool isKeyPressed(int id, Action action);
        static bool isKeyReleased(int id, Action action);
        static bool isKeyHeld(int id, Action action);

        static bool isGamepad(int id);

        static float axis(int id, Axis axis);

    private:
        int up[PLAYERS][BUTTONS];
        int down[PLAYERS][BUTTONS];
        bool gamepad[PLAYERS];
        unsigned int key[PLAYERS][BUTTONS];
        unsigned int gamepadID[PLAYERS];

        static Input *input;

};

}

#endif

