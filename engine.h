#ifndef H_ENGINE
#define H_ENGINE

#include <SFML/Graphics.hpp>

class Textures;

class Engine
{
private:
    static Engine* engine;
    Textures* textures;
    sf::RenderWindow* window;

public:
    Engine();
    ~Engine();
    static Engine* getEngine();

    void loop();
    Textures* getTextures();
};

#endif