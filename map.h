#ifndef H_MAP
#define H_MAP
#include <vector>
#include <SFML/Graphics.hpp>

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

private:
	std::vector<Thing*> things;
	Bullets* bullets;
};

#endif // !H_MAP