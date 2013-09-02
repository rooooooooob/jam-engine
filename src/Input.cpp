#include "Input.hpp"

#include <cstddef>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>

namespace je
{

Input *Input::input = NULL;

Input::Input()
{
    input = this;
    int gamepadsUsed = 0;
    for (int id = 0; id < PLAYERS; ++id)
    {
        for (int b = 0; b < BUTTONS; ++b)
        {
            up[id][b] = 0;
            down[id][b] = 0;
        }
        gamepad[id] = false;
        std::stringstream ss;
        ss << "settings/controls" << id << ".txt";
        FILE *file = fopen(ss.str().c_str(), "r+");
        if (file)
        {
            printf("Loading %s\n", ss.str().c_str());
            int buffer;
            fscanf(file, "%d", &buffer);
            gamepad[id] = buffer;
            gamepadID[id] = gamepadsUsed;
            if (buffer)
                ++gamepadsUsed;
            for (int b = 0; b < BUTTONS; ++b){
                fscanf(file, "%d", (int*) key[id] + b);
                printf("Loaded key %d to %d\n", b, key[id][b]);}
            fclose(file);
        }
        else
        {
            printf("Error: couldn't open %s\n", ss.str().c_str());
        }
    }

}

Input::~Input()
{
    input = NULL;
}

void Input::update()
{
    for (int id = 0; id < PLAYERS; ++id)
    {
        for (int b = 0; b < BUTTONS; ++b)
        {
            if ((gamepad[id] && sf::Joystick::isButtonPressed(gamepadID[id], key[id][b]))
                || (!gamepad[id] && sf::Keyboard::isKeyPressed((sf::Keyboard::Key) key[id][b])))
            {
                down[id][b] = 2;
                if (up[id][b] > 0)
                    --up[id][b];
            }
            else
            {
                up[id][b] = 2;
                if (down[id][b] > 0)
                    --down[id][b];
            }
        }
    }
}

/*          static methods now              */
bool Input::isKeyPressed(int id, Action action)
{
    return input && input->up[id][action] == 1;
}

bool Input::isKeyReleased(int id, Action action)
{
    return input && input->down[id][action] == 1;
}

bool Input::isKeyHeld(int id, Action action)
{
    return input && input->down[id][action] == 2;
}

bool Input::isGamepad(int id)
{
    return input && input->gamepad[id];
}

float Input::axis(int id, Axis axis)
{
    if (!input || (input && !input->gamepad[id]))
        return 0;
    else
        return sf::Joystick::getAxisPosition(input->gamepadID[id], axis) / 100.f;
}

}
