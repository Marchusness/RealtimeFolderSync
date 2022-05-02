#include "thing.h"
#include "engine.h"

Thing::Thing()
{
    sprite;
    sprite.setTexture(*Engine::getTexture("block1x1"));
    posX = 0;
    posY = 0;
    velX = 0.01;
    velY = 0.01;
}

Thing::~Thing()
{
}

void Thing::update()
{
	posX += velX;
	posY += velY;
}

void Thing::draw()
{
    //just quick test stuff
    sprite.setColor(sf::Color(0, 255, 0));
    sprite.setPosition(sf::Vector2f(posX, posY));
    sprite.setScale(0.5f, 0.5f);
    Engine::getWindow()->draw(sprite);
}