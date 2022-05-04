#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "game_singleplayer.h"
#include "engine.h"
#include "textures.h"
#include "map.h"
#include "thing.h"

Game_Singleplayer::Game_Singleplayer()
{
    map = new Map();

    //you can slap test stuff here like creating blocks and adding them to the map or something idk
    Thing* thing = new Thing(map->getWorld());
    map->addThing(thing);
}

Game_Singleplayer::~Game_Singleplayer()
{
    delete map;
}

void Game_Singleplayer::update()
{
    map->update();
}

void Game_Singleplayer::draw()
{
    //clear the screen
    Engine::getWindow()->clear(sf::Color(10, 10, 10));

    map->draw();
}