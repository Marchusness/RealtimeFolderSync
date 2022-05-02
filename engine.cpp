#include <iostream>
#include "engine.h"
#include "textures.h"
#include "scene.h"
#include "game_singleplayer.h"

Engine* Engine::engine = nullptr;

Engine::Engine()
{
    if (engine == nullptr)
    {
        engine = this;
    }

    sf::Clock clock;

    std::cout << "loading textures" << std::endl;
    textures = new Textures();

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Major Project", sf::Style::Titlebar | sf::Style::Close );
    currentScene = (Scene* )new Game_Singleplayer();

    //some magic will happen with this one
    //using funcp = Scene * (*)();
    //sceneCreateres.insert(std::make_pair<std::string, funcp>("game_singleplayer", &createScene<Game_Singleplayer>));
}

Engine::~Engine()
{
    delete textures;
    if (currentScene != nullptr) delete currentScene;
}

Engine* Engine::getEngine() { return engine; }

void Engine::loop()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        previousFrameTime = deltaTimeClock.getElapsedTime();
        deltaTimeClock.restart();
        currentScene->update();
        currentScene->draw();
        window->display();
    }
}

Textures* Engine::getTextures() { return engine->textures; }

sf::Texture* Engine::getTexture(std::string name)
{
    return engine->textures->getTexture(name);
}

sf::RenderWindow* Engine::getWindow() { return engine->window; }

sf::Int32 Engine::getDetaTime() { return engine->previousFrameTime.asMilliseconds(); }

/* more magic to come
template <typename T>
Scene* Engine::createScene()
{
    return new T;
}
*/