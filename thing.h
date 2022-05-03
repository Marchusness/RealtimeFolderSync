#ifndef H_THING
#define H_THING
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Thing
{
public:
	Thing(b2World* world);
	~Thing();

	void update();
	void draw();

	void setPos(float x, float y);
	void setVel(float x, float y);
	float addVel(float x, float y);

private:
	sf::Sprite sprite;
	b2Body* body;
};

#endif // !H_THING
