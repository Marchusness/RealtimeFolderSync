#include <iostream>
#include "engine.h"

int main()
{
    Engine engine;
    engine.loop();
    return 1;
}

// g++ -std=c++17 MajorProject.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -o test -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-graphics -lsfml-window -lsfml-system -v