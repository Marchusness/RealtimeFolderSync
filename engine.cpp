#include <iostream>
#include "engine.h"
#include "textures.h"

Engine* Engine::engine = nullptr;

Engine::Engine()
{
    if (engine == nullptr)
    {
        engine = this;
    }
    std::cout << "loading textures" << std::endl;
    textures = new Textures();

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Major Project", sf::Style::Titlebar | sf::Style::Close );
}

Engine::~Engine()
{
    delete textures;
}

Engine* Engine::getEngine() { return engine; }

void Engine::loop()
{
    //just quick test stuff
    sf::Sprite sprite;
    sprite.setTexture(*textures->getTexture("block1x1"));
    sprite.setColor(sf::Color(0, 255, 0));
    sprite.setPosition(sf::Vector2f(10.f, 50.f));
    sprite.setScale(0.5f, 0.5f);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color(10, 10, 10));
        window->draw(sprite);
        window->display();
    }
}

Textures* Engine::getTextures() { return textures; }