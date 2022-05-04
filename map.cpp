#include <box2d/box2d.h>
#include "map.h"
#include "thing.h"

Map::Map()
{
	b2Vec2 gravity(0.f, 0.05f);
	world = new b2World(gravity);
}

Map::~Map()
{
	delete world;
}

void Map::update()
{
	world->Step(1 / 60.f, 8, 3);
	for (auto it = things.begin(); it != things.end(); it++)
	{
		(*it)->update();
	}
}

void Map::draw()
{
	for (auto it = things.begin(); it != things.end(); it++)
	{
		(*it)->draw();
	}
}

void Map::addThing(Thing* thing)
{
	things.push_back(thing);
}

b2World* Map::getWorld()
{
	return world;
}