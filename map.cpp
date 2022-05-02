#include "map.h"
#include "thing.h"

Map::Map()
{

}

Map::~Map()
{
}

void Map::update()
{
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