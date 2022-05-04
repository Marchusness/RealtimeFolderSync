#ifndef H_MAP
#define H_MAP
#include <vector>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Thing;
class Bullets;

class Map
{
public:
	Map();
	~Map();

	void update();
	void draw();

	void addThing(Thing* thing);
	b2World* getWorld();

private:
	std::vector<Thing*> things;
	Bullets* bullets;
	b2World* world;    //a box2d thing
};

#endif // !H_MAP