#include <SFML/Graphics.hpp>
#include <array>

#include "core.hpp"

#include <iostream>
#include <cmath>

int main()
{
    Game joc(1280, 720, "KiDefend");

    while (joc.window->isOpen())
    {
        joc.run();
    }
}